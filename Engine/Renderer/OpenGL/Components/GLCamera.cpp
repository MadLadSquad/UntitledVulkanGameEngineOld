// GLCamera.cpp
// Last update 4/12/2021 by Madman10K
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

	recalculate();
}

void UVK::GLCamera::move(float deltaTime)
{
    if (UVK::Input::getMouseKeyPressed(Keys::MouseButtonRight))
    {
        currentWindow.setCursorVisibility(false);

        if (UVK::Input::getKeyPressed(Keys::W))
        {
            position += front * moveSpeed * deltaTime;
        }
        if (UVK::Input::getKeyPressed(Keys::S))
        {
            position -= front * moveSpeed * deltaTime;
        }
        if (UVK::Input::getKeyPressed(Keys::A))
        {
            position -= right * moveSpeed * deltaTime;
        }
        if (UVK::Input::getKeyPressed(Keys::D))
        {
            position += right * moveSpeed * deltaTime;
        }
        if (UVK::Input::getKeyPressed(Keys::Q))
        {
            position -= worldUp * moveSpeed * deltaTime;
        }
        if (UVK::Input::getKeyPressed(Keys::E))
        {
            position += worldUp * moveSpeed * deltaTime;
        }

    }
    else
    {
        currentWindow.setCursorVisibility(true);
    }
}

void UVK::GLCamera::moveMouse(float deltaTime, FVector2 change)
{
    if (UVK::Input::getMouseKeyPressed(Keys::MouseButtonRight))
    {
        change.x *= turnSpeed * deltaTime;
        change.y *= turnSpeed * deltaTime;

        yaw += change.x;
        pitch += change.y;

        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }

        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
    }
    
    recalculate();
}

glm::mat4 UVK::GLCamera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void UVK::GLCamera::recalculate()
{
	front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front.y = glm::sin(glm::radians(pitch));
	front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}