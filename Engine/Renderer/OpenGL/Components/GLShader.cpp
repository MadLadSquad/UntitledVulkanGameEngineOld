// GLShader.cpp
// Last update 3/17/2021 by Madman10K
#include "GLShader.hpp"

void UVK::GLShader::createFromString(const char* vertex, const char* fragment)
{
	compileShader(vertex, fragment);
}

void UVK::GLShader::createFromFile(const char* vLocation, const char* fLocation)
{
	compileShader(readFile(vLocation).c_str(), readFile(fLocation).c_str());
}

std::string UVK::GLShader::readFile(const char* location)
{
	std::string content;
	std::ifstream fileStream(location, std::ios::in);

	if (!fileStream.is_open()) {
		logger.consoleLog("Failed to read file at location:", UVK_LOG_TYPE_ERROR, location);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint UVK::GLShader::getProjectionLocation()
{
	return uniformProjection;
}

GLuint UVK::GLShader::getModelLocation()
{
	return uniformModel;
}

GLuint UVK::GLShader::getViewLocation()
{
	return uniformView;
}

void UVK::GLShader::useShader()
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

void UVK::GLShader::compileShader(const char* vertex, const char* fragment)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		logger.consoleLog("Failed to create shader program", UVK_LOG_TYPE_ERROR);
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
		glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
		logger.consoleLog("Error linking program", UVK_LOG_TYPE_ERROR, errorLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
		logger.consoleLog("Error validating program", UVK_LOG_TYPE_ERROR, errorLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");
}

void UVK::GLShader::addShader(GLuint program, std::string shader, GLenum shaderType)
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
		glGetShaderInfoLog(theShader, sizeof(errorLog), NULL, errorLog);
		logger.consoleLog("Failed to compile shader with type", UVK_LOG_TYPE_ERROR, shaderType, errorLog);
		return;
	}

	glAttachShader(program, theShader);
}