// GLShader.hpp
// Last update 4/20/2021 by Madman10K
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

		[[nodiscard]] GLuint getProjectionLocation() const;
		[[nodiscard]] GLuint getModelLocation() const;
		[[nodiscard]] GLuint getViewLocation() const;

		void useShader() const;
		void clearShader();

	private:
		GLuint shaderID, uniformProjection, uniformModel, uniformView;
		
		static std::string readFile(const char* location);
		
		void compileShader(const char* vertex, const char* fragment);
		static void addShader(GLuint program, std::string shader, GLenum shaderType);
    };

	class GLShaderSPV
    {
    public:
        GLShaderSPV() = default;
        GLShaderSPV(const char* vLoc, const char* fLoc)
        {
            readFile(vLoc, fLoc);
        }

        void useShader() const;

    private:
        GLuint shaderID = 0;
        std::vector<unsigned char> vShader{};
        std::vector<unsigned char> fShader{};

        void compileShader();

        void readFile(const char* vertexLocation, const char* fragmentLocation);
    };
}


