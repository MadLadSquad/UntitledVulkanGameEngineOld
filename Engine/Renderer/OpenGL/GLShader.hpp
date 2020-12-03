#pragma once
#include "../../Core/API/Defines.h"

#ifdef Legacy
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "../../ThirdParty/GLEW/include/GL/glew.h"

namespace UVK
{
	class UVK_API GLShader
	{
	public:
		GLShader();

		void CreateFromString(const char* Vertex, const char* Fragment);
		void CreateFromFiles(const char* VertexLocation, const char* FragmentLocation);

		std::string ReadFile(const char* FileLocation);

		GLuint GetProjectionLocation();
		GLuint GetModelLocation();
		GLuint GetViewLocation();

		void UseShader();
		void ClearShader();

		~GLShader();

	private:
		GLuint ShaderID, UniformProjection, UniformModel, UniformView;

		void CompileShader(const char* Vertex, const char* Fragment);
		void AddShader(GLuint Program, const char* Shader, GLenum ShaderType);
	};
}
#endif