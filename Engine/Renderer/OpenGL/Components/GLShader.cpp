// GLShader.cpp
// Last update 4/20/2021 by Madman10K
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

	std::string line;
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint UVK::GLShader::getProjectionLocation() const
{
	return uniformProjection;
}

GLuint UVK::GLShader::getModelLocation() const
{
	return uniformModel;
}

GLuint UVK::GLShader::getViewLocation() const
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
		glGetProgramInfoLog(shaderID, sizeof(errorLog), nullptr, errorLog);
		logger.consoleLog("Error linking program", UVK_LOG_TYPE_ERROR, errorLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(errorLog), nullptr, errorLog);
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
		glGetShaderInfoLog(theShader, sizeof(errorLog), nullptr, errorLog);
		logger.consoleLog("Failed to compile shader with type", UVK_LOG_TYPE_ERROR, shaderType, errorLog);
		return;
	}

	glAttachShader(program, theShader);
}

void UVK::GLShaderSPV::readFile(const char* vertexLocation, const char* fragmentLocation)
{
    std::ifstream vertexInput(vertexLocation, std::ios::binary);
    std::ifstream fragmentInput(fragmentLocation, std::ios::binary);

    vShader = std::vector<unsigned char>(std::istreambuf_iterator<char>(vertexInput), {});
    fShader = std::vector<unsigned char>(std::istreambuf_iterator<char>(fragmentInput), {});
}

void UVK::GLShaderSPV::compileShader()
{
    readFile("../Content/Engine/vShader.spv", "../Content/Engine/fShader.spv");

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderBinary(1, &vertexShader, GL_SHADER_BINARY_FORMAT_SPIR_V, vShader.data(), vShader.size());
    glShaderBinary(1, &fragmentShader, GL_SHADER_BINARY_FORMAT_SPIR_V, fShader.data(), fShader.size());

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
        logger.consoleLog("Error in compiling vertex shader! Log: ", UVK_LOG_TYPE_ERROR, infoLog.data());
        glDeleteShader(vertexShader);

        GLint maxLengthF = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLogF(maxLengthF);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        logger.consoleLog("Error in compiling fragment shader! Log: ", UVK_LOG_TYPE_ERROR, infoLogF.data());

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

        logger.consoleLog("Could not link program, Error: ", UVK_LOG_TYPE_ERROR, infoLog.data());

        glDeleteProgram(shaderID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderID, vertexShader);
    glDetachShader(shaderID, fragmentShader);
}

void UVK::GLShaderSPV::useShader() const
{
    glUseProgram(shaderID);
}
