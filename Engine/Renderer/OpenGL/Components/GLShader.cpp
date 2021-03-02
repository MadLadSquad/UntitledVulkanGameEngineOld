// GLShader.cpp
// Last update 3/2/2021 by Madman10K
#include "GLShader.hpp"

void UVK::GLShader::clearShader()
{

}

void UVK::GLShader::createShader()
{
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderBinary(1, &vShader, GL_SHADER_BINARY_FORMAT_SPIR_V, vertexShader.data(), vertexShader.size());

    std::string vsEntrypoint = "main";
    glSpecializeShader(vShader, (const GLchar*)vsEntrypoint.c_str(), 0, nullptr, nullptr);

    GLint isCompiled = 0;
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(vShader);
        return;
    }

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderBinary(1, &fShader, GL_SHADER_BINARY_FORMAT_SPIR_V, fragmentShader.data(), fragmentShader.size());

    std::string fsEntrypoint = "main"; //Get VS entry point name
    glSpecializeShader(fShader, (const GLchar*)fsEntrypoint.c_str(), 0, nullptr, nullptr);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(fShader);

        glDeleteShader(vShader);

        return;
    }
    GLuint program = glCreateProgram();

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);

        glDeleteShader(vShader);
        glDeleteShader(fShader);

        return;
    }

    glDetachShader(program, vShader);
    glDetachShader(program, fShader);
}

void UVK::GLShader::addShader(const char* vLoc, const char* fLoc)
{
    
}
