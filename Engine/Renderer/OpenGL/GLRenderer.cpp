// GLRenderer.hpp
// Last update 1/10/2021 by Madman10K
#include "GLRenderer.hpp"


const GLint WIDTH = 800, HEIGHT = 600;
GLuint VBO, VAO, shader;
static const char* vShader = R"(
#version 330

layout (location = 0) in vec3 pos;

void main()
{
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
})";

static const char* fShader = R"(
#version 330

out vec4 colour;

void main()
{
    colour = vec4(1.0, 0.0, 0.0, 1.0);
})";


void UVK::GLRenderer::createWindow()
{
    if (!glfwInit())
    {
        logger.consoleLog("GLFW initialisation failed!", ERROR);
        glfwTerminate();
        return;
    }
    logger.consoleLog("Setting up the window", NOTE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    if (!mainWindow)
    {
        logger.consoleLog("GLFW window creation failed!", ERROR);
        glfwTerminate();
        return;
    }
    logger.consoleLog("Window was created successfully", SUCCESS);
    // Get Buffer Size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        logger.consoleLog("GLEW initialisation failed!", ERROR);

        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return;
    }

    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    logger.consoleLog("Creating geometry", NOTE);
    createTriangle();
    compileShaders();
    logger.consoleLog("Compiled Shaders", SUCCESS);
    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }
}

void UVK::GLRenderer::createTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void UVK::GLRenderer::addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = static_cast<std::string>(shaderCode).length();

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar ErrorLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, 1024, NULL, ErrorLog);
        logger.consoleLogComplex<GLchar*>("Error compiling the a shader:", ERROR, {ErrorLog});
        return;
    }

    glAttachShader(theProgram, theShader);
}

void UVK::GLRenderer::compileShaders()
{
    shader = glCreateProgram();

    if (!shader)
    {
        logger.consoleLog("Failed to create shader", ERROR);
        return;
    }

    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(ErrorLog), NULL, ErrorLog);
        logger.consoleLogComplex<GLchar*>("Error linking program:", ERROR, {ErrorLog});
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(ErrorLog), NULL, ErrorLog);
        logger.consoleLogComplex<GLchar*>("Error validating program:", ERROR, {ErrorLog});
        return;
    }
}
