// GLCamera.hpp
// Last update 3/23/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <Events/Input/InputSystem.hpp>

namespace UVK
{
	class GLCamera
	{
	public:
		GLCamera() = delete;
		GLCamera(FVector position, FVector up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed);
	
	
		void move();
	
		glm::mat4 calculateViewMatrix();


		FVector position;
		FVector front;
		FVector up;
		FVector right;
		FVector worldUp;

		GLfloat yaw;
		GLfloat pitch;

		GLfloat moveSpeed;
		GLfloat turnSpeed;
	private:

		bool holdingRight = false;

		/*FVector position;
		FVector front;
		FVector up;
		FVector right;
		FVector worldUp;

		GLfloat yaw;
		GLfloat pitch;

		GLfloat moveSpeed;
		GLfloat turnSpeed;
		*/
		void update();

		//friend class GLRenderer;
	};
}