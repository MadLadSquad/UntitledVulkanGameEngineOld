#pragma once
#include "../../Core/API/Defines.h"
#include "../../Core/API/Types.hpp"

#ifdef Legacy
#include "../../ThirdParty/GLEW/include/GL/glew.h"
#include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
#include "../../ThirdParty/glm/glm/glm.hpp"
#include "../../ThirdParty/glm/glm/gtc/matrix_transform.hpp"

namespace UVK
{
	class UVK_API GLCamera
	{
	public:
		GLCamera();
		void InitCamera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
		~GLCamera();

		glm::mat4 CalculateViewMat();

		GLfloat MovementSpeed;
		GLfloat TurnSpeed;
		
		void Control(bool* keys, GLfloat deltaTime);
		void MouseControl(GLfloat xChange, GLfloat yChange);
	private:	
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;

		GLfloat yaw;
		GLfloat pitch;

		GLfloat moveSpeed;
		GLfloat turnSpeed;
	
		void Update();
	};
}

#endif