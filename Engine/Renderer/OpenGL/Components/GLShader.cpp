// GLShader.cpp
// Last update 2/7/2021 by Madman10K
#include <GL/glew.h>
#include "GLShader.hpp"

void UVK::GLShader::createFromString(UVK::String vertex, UVK::String fragment)
{
	compileShader(vertex, fragment);
}

void UVK::GLShader::createFromFile(UVK::String vLocation, UVK::String fLocation)
{
	compileShader(readFile(vLocation).c_str(), readFile(fLocation).c_str());
}

UVK::FString UVK::GLShader::readFile(UVK::String location)
{
	std::string content;
	std::ifstream fileStream(location, std::ios::in);

	if (!fileStream.is_open()) {
		Logger::log("Failed to read file at location:", UVK_LOG_TYPE_ERROR, location);
		return "";
	}

	std::string line;
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

uint32_t UVK::GLShader::getProjectionLocation() const
{
	return uniformProjection;
}

uint32_t UVK::GLShader::getModelLocation() const
{
	return uniformModel;
}

uint32_t UVK::GLShader::getViewLocation() const
{
	return uniformView;
}

void UVK::GLShader::useShader() const
{
	glUseProgram(shaderID);
}

void UVK::GLShader::clearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

void UVK::GLShader::compileShader(UVK::String vertex, UVK::String fragment)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		Logger::log("Failed to create shader program", UVK_LOG_TYPE_ERROR);
		return;
	}

	addShader(shaderID, vertex, GL_VERTEX_SHADER);
	addShader(shaderID, fragment, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(errorLog), nullptr, errorLog);
		Logger::log("Error linking program", UVK_LOG_TYPE_ERROR, errorLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(errorLog), nullptr, errorLog);
		Logger::log("Error validating program", UVK_LOG_TYPE_ERROR, errorLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");
}

void UVK::GLShader::addShader(GLuint program, const UVK::FString& shader, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	
	GLint codeLength = shader.length();
	auto a = shader.c_str();

	glShaderSource(theShader, 1, &a, &codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar errorLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(errorLog), nullptr, errorLog);
		Logger::log("Failed to compile shader with type", UVK_LOG_TYPE_ERROR, shaderType, errorLog);
		return;
	}

	glAttachShader(program, theShader);
}

void UVK::GLShaderSPV::readFile(UVK::String location)
{
    std::ifstream input(location, std::ios::binary);

    buffer = std::vector<uint32_t>(std::istreambuf_iterator<char>(input), {});
}

void UVK::GLShaderSPV::compileShader()
{
    GLuint program = glCreateProgram();
    shaderID = glCreateShader(format);
    glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
    glAttachShader(program, shaderID);

    glLinkProgram(program);

    GLint bLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &bLinked);
    if (bLinked == GL_FALSE)
    {
        GLint len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        char str[1024];
        str[1023] = '\0';
        glGetProgramInfoLog(program, len, &len, str);

        Logger::log("OpenGL error: ", UVK_LOG_TYPE_ERROR, (const char*)str);

        glDeleteProgram(program);
        glDeleteShader(shaderID);
    }

    glDetachShader(program, shaderID);
    glDeleteShader(shaderID);
    /*
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderBinary(1, &vertexShader, GL_SHADER_BINARY_FORMAT_SPIR_V, vShader.data(), vShader.size() * sizeof(uint32_t));
    glShaderBinary(1, &fragmentShader, GL_SHADER_BINARY_FORMAT_SPIR_V, fShader.data(), fShader.size() * sizeof(uint32_t));

    glSpecializeShader(vertexShader, "main", 0, nullptr, nullptr);
    glSpecializeShader(fragmentShader, "main", 0, nullptr, nullptr);

    GLint vertexResult = 0;
    GLint fragmentResult = 0;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexResult);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentResult);
    if (vertexResult == GL_FALSE && fragmentResult == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        Logger::log("Error in compiling vertex shader! Log: ", UVK_LOG_TYPE_ERROR, infoLog.data());
        glDeleteShader(vertexShader);

        GLint maxLengthF = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLogF(maxLengthF);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        Logger::log("Error in compiling fragment shader! Log: ", UVK_LOG_TYPE_ERROR, infoLogF.data());

        glDeleteShader(fragmentShader);
        return;
    }

    shaderID = glCreateProgram();

    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);

    glLinkProgram(shaderID);

    GLint isLinked = 0;
    glGetProgramiv(shaderID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

        Logger::log("Could not link program, Error: ", UVK_LOG_TYPE_ERROR, infoLog.data());

        glDeleteProgram(shaderID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderID, vertexShader);
    glDetachShader(shaderID, fragmentShader);
     */
}

void UVK::GLShaderSPV::useShader() const
{
    glUseProgram(shaderID);
}
