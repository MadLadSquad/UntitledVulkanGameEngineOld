// GLCamera.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    /**
     * @brief OpenGL specific camera class
     */
	class GLCamera
	{
	public:
		GLCamera() = default;
		GLCamera(FVector position, FVector up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed);
	
	
		void move(float deltaTime);
		void moveMouse(float deltaTime, FVector2 change);

		glm::mat4 calculateViewMatrix();

		[[nodiscard]] float getYaw() const
		{
			return yaw;
		}

		[[nodiscard]] float getPitch() const
		{
			return pitch;
		}

		[[nodiscard]] float getMovementSpeed() const
		{
			return moveSpeed;
		}

		[[nodiscard]] float getTurnSpeed() const
		{
			return turnSpeed;
		}

		FVector getPosition()
		{
			return position;
		}
	private:

		bool holdingRight = false;

		FVector position{};
		FVector front{};
		FVector up{};
		FVector right{};
		FVector worldUp{};

		GLfloat yaw = 0;
		GLfloat pitch = 0;

		GLfloat moveSpeed = 0;
		GLfloat turnSpeed = 0;

		void recalculate();
	};
}