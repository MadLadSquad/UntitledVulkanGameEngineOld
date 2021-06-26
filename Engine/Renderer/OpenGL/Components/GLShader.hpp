// GLShader.hpp
// Last update 26/6/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <UVKLog.h>
#include <string>
#include <vector>
#include <Core/Types.hpp>
//#include <Core.hpp>

namespace UVK
{
    /**
     * @brief Shader impost types are file, string, spir
     */
	enum ShaderImportType
	{
		SHADER_IMPORT_TYPE_FILE,
		SHADER_IMPORT_TYPE_STRING,
		SHADER_IMPORT_TYPE_SPIR
	};
    /**
     * @brief OpenGL specific text shader class
     */
	class GLShader
    {
    public:
		GLShader() = default;

		void createFromString(UVK::String vertex, UVK::String fragment);
		void createFromFile(UVK::String vLocation, UVK::String fLocation);

		[[nodiscard]] GLuint getProjectionLocation() const;
		[[nodiscard]] GLuint getModelLocation() const;
		[[nodiscard]] GLuint getViewLocation() const;

		void useShader() const;
		void clearShader();

	private:
		GLuint shaderID, uniformProjection, uniformModel, uniformView;
		
		static std::string readFile(UVK::String location);
		
		void compileShader(UVK::String vertex, UVK::String fragment);
		static void addShader(GLuint program, const std::string& shader, GLenum shaderType);
    };

    /**
     * @brief OpenGL specific spirv shader class
     */
	class GLShaderSPV
    {
    public:
        GLShaderSPV() = default;
        GLShaderSPV(UVK::String vLoc, UVK::String fLoc)
        {
            readFile(vLoc, fLoc);
        }

        void useShader() const;

    private:
        GLuint shaderID = 0;
        std::vector<unsigned char> vShader{};
        std::vector<unsigned char> fShader{};

        void compileShader();

        void readFile(UVK::String vertexLocation, UVK::String fragmentLocation);
    };
}


