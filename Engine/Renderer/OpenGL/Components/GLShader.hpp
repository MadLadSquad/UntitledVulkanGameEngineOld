// GLShader.hpp
// Last update 2/7/2021 by Madman10K
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
    enum ShaderFormat
    {
        SHADER_FORMAT_VERTEX = 0x8B31,
        SHADER_FORMAT_FRAGMENT = 0x8B30,
        SHADER_FORMAT_GEOMETRY = 0x8DD9,
        SHADER_FORMAT_COMPUTE = 0x91B9
    };

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
        GLShaderSPV(UVK::String location, ShaderFormat fmt)
        {
            format = fmt;
            readFile(location);
        }

        void useShader() const;

        std::vector<uint32_t>& getBuffer()
        {
            return buffer;
        }

        GLuint& getID()
        {
            return shaderID;
        }
    private:
        GLuint shaderID = 0;
        std::vector<uint32_t> buffer{};
        ShaderFormat format;

        void compileShader();

        void readFile(UVK::String location);
    };
}


