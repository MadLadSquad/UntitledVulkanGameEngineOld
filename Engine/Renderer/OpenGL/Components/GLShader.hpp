// GLShader.hpp
// Last update 3/17/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <UVKLog.h>
#include <string>
//#include <Core.hpp>

namespace UVK
{
	enum ShaderImportType
	{
		SHADER_IMPORT_TYPE_FILE,
		SHADER_IMPORT_TYPE_STRING,
		SHADER_IMPORT_TYPE_SPIR
	};
	
	class GLShader
    {
    public:
		GLShader() = default;

		void createFromString(const char* vertex, const char* fragment);
		void createFromFile(const char* vLocation, const char* fLocation);

		GLuint getProjectionLocation();
		GLuint getModelLocation();
		GLuint getViewLocation();

		void useShader();
		void clearShader();

	private:
		GLuint shaderID, uniformProjection, uniformModel, uniformView;
		
		std::string readFile(const char* location);
		
		void compileShader(const char* vertex, const char* fragment);
		void addShader(GLuint program, std::string shader, GLenum shaderType);
    };
}


