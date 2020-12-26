// PlayerController.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
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


void UVK::GLRenderer::CreateWindow()
{
// Initialise GLFW
    if (!glfwInit())
    {
        Log.ConsoleLog("GLFW initialisation failed!", ERROR);
        glfwTerminate();
        return;
    }
    Log.ConsoleLog("Setting up the window", NOTE);
    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow Forward Compatbility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    if (!mainWindow)
    {
        Log.ConsoleLog("GLFW window creation failed!", ERROR);
        glfwTerminate();
        return;
    }
    Log.ConsoleLog("Window was created successfully", SUCCESS);
    // Get Buffer Size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        Log.ConsoleLog("GLEW initialisation failed!", ERROR);

        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return;
    }

    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    Log.ConsoleLog("Creating geometry", NOTE);
    CreateTriangle();
    CompileShaders();
    Log.ConsoleLog("Compiled Shaders", SUCCESS);
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

void UVK::GLRenderer::CreateTriangle()
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

void UVK::GLRenderer::AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar ErrorLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, 1024, NULL, ErrorLog);
        Log.ConsoleLogComplex<GLchar*>("Error compiling the a shader:", ERROR, {ErrorLog});
        return;
    }

    glAttachShader(theProgram, theShader);
}

void UVK::GLRenderer::CompileShaders()
{
    shader = glCreateProgram();

    if (!shader)
    {
        Log.ConsoleLog("Failed to create shader", ERROR);
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(ErrorLog), NULL, ErrorLog);
        Log.ConsoleLogComplex<GLchar*>("Error linking program:", ERROR, {ErrorLog});
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(ErrorLog), NULL, ErrorLog);
        Log.ConsoleLogComplex<GLchar*>("Error validating program:", ERROR, {ErrorLog});
        return;
    }
}
