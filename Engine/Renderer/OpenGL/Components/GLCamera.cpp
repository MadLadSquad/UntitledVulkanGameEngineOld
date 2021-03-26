// GLCamera.cpp
// Last update 3/23/2021 by Madman10K
#include "../../Window/Window.hpp"
#include "GLCamera.hpp"


UVK::GLCamera::GLCamera(FVector position, FVector up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed)
{
	this->position = position;
	worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	front = FVector(0.0f, 0.0f, -1.0f);

	moveSpeed = movementSpeed;
	this->turnSpeed = turnSpeed;

	update();
}

void UVK::GLCamera::move(float deltaTime)
{
    if (currentWindow.mouseArr[Keys::MouseButtonRight])
    {
        currentWindow.setCursorVisibility(false);

        if (currentWindow.keysArr[Keys::W])
        {
            position += front * moveSpeed * deltaTime;
        }
        if (currentWindow.keysArr[Keys::S])
        {
            position -= front * moveSpeed * deltaTime;
        }
        if (currentWindow.keysArr[Keys::A])
        {
            position -= right * moveSpeed * deltaTime;
        }
        if (currentWindow.keysArr[Keys::D])
        {
            position += right * moveSpeed * deltaTime;
        }
        if (currentWindow.keysArr[Keys::Q])
        {
            position -= up * moveSpeed * deltaTime;
        }
        if (currentWindow.keysArr[Keys::E])
        {
            position += up * moveSpeed * deltaTime;
        }

    }
    else
    {
        currentWindow.setCursorVisibility(true);
    }
}

void UVK::GLCamera::moveMouse(float deltaTime, float xChange, float yChange)
{
    if (currentWindow.mouseArr[Keys::MouseButtonRight])
    {
        xChange *= turnSpeed * deltaTime;
        yChange *= turnSpeed * deltaTime;

        yaw += xChange;
        pitch += yChange;

        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }

        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
    }
    update();
}

glm::mat4 UVK::GLCamera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void UVK::GLCamera::update()
{
	front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front.y = glm::sin(glm::radians(pitch));
	front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}