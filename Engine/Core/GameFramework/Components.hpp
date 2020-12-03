#pragma once
#include "../API/Defines.h"
#include "../API/Types.hpp"
#include "../../Audio/AudioCore.hpp"
#include "../../Renderer/RendererCore.hpp"

namespace UVK
{
	/*
		@brief A component containing an array of vertices. This should be used only as debug because in production you would want to use 3D models and asset references
	*/
	struct MeshComponentRaw
	{
		void CreateMesh(GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, GLWindow* window)
		{
			UniformProjection = 0;
			UniformModel = 0;
			UniformView = 0;
			bMovesWithKeys = false;
			bMovesWithMouse = false;
			
			obj = new UVK::GLMesh();
			obj->CreateMesh(vertices, indices, vertexNum, indexNum);
		
			camera = new UVK::GLCamera;
			this->window = window;
		}

		void CreateShader(String VertexShader, String FragmentShader)
		{
			shader = new UVK::GLShader();
			shader->CreateFromFiles(VertexShader, FragmentShader);
		}
	
		GLMesh* GetMesh()
		{
			return obj;
		}

		GLShader* GetShader()
		{
			return shader;
		}

		void UseShader()
		{
			shader->UseShader();
			
			UniformModel = shader->GetModelLocation();
			UniformProjection = shader->GetProjectionLocation();
			UniformView = shader->GetViewLocation();
			
			camera->InitCamera(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
			Projection = glm::perspective(120.0f, 800.0f / 600.0f, 0.1f, 100.0f);
			
			glUniformMatrix4fv(UniformProjection, 1, GL_FALSE, glm::value_ptr(Projection));
			glUniformMatrix4fv(UniformView, 1, GL_FALSE, glm::value_ptr(camera->CalculateViewMat()));
		}

		void CleanUp()
		{
			obj->~GLMesh();
			delete obj;
			shader->~GLShader();
			delete shader;
			delete camera;
		}

		void SetCamera(bool bMovesWithKeys, bool bMovesWithMouse)
		{
			this->bMovesWithKeys = bMovesWithKeys;
			this->bMovesWithMouse = bMovesWithMouse;
		}

		void UseCamera()
		{
			camera->Control(window->GetKeys(), 27);
			
			camera->MouseControl(window->GetMouseXChange(), window->GetMouseYChange());
		}

		void Render(glm::mat4 model)
		{
			glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
			
			obj->RenderMesh();

			glUseProgram(0);
		}
	private:
		GLShader* shader;
		GLMesh* obj;
		GLCamera* camera;
		GLWindow* window;

	private:
		GLuint UniformProjection;
		GLuint UniformModel;
		GLuint UniformView;
		
		bool bMovesWithKeys;
		bool bMovesWithMouse;

		glm::mat4 Projection;
	};

	/*
		@brief Component for playing audio
	*/
	struct AudioComponent
	{
		void PlayAudio()
		{
			UVK::AudioRenderer audio;

			audioThread = std::thread([&]() { audio.PlaySimpleAudio(FileLocation); });
		}
	
		void SetFileLocation(String location)
		{
			FileLocation = location;
		}

		void DeleteAudio()
		{
			audioThread.join();
		}
	private:
		std::thread audioThread;
		String FileLocation;
	};

	/*
		@brief Component for a point light. Coming soon!
	*/
	struct PointLightComponent
	{

	};

	/*
		@brief Component for a directional light. Coming soon!
	*/
	struct DirectionalLightComponent
	{

	};

	/*
		@brief Component for post processing
	*/
	struct PostProcessComponent
	{

	};
}
