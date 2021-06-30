// MeshComponentRaw.cpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include "MeshComponentRaw.hpp"
#include <Engine/Core/Core/Global.hpp>

void UVK::MeshComponentRaw::createMesh(GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, UVK::String vertexShader, UVK::String fragmentShader, ShaderImportType type)
{
    fShader = fragmentShader;
    vShader = vertexShader;
    impType = type;
    for (int i = 0; i < indexNum; i++)
    {
        index.push_back(indices[i]);
    }

    for (int i = 0; i < vertexNum; i++)
    {
        vertex.push_back(vertices[i]);
    }

    mesh.createMesh(vertices, indices, vertexNum, indexNum);

    switch (type)
    {
        case SHADER_IMPORT_TYPE_FILE:
            shader.createFromFile(vertexShader, fragmentShader);
            break;
        case SHADER_IMPORT_TYPE_STRING:
            shader.createFromString(vertexShader, fragmentShader);
            break;
        case SHADER_IMPORT_TYPE_SPIR:
            logger.consoleLog("SPIR-V in OpenGL not implemented yet!", UVK_LOG_TYPE_ERROR);
            break;
    }

    translation = FVector(0.0f, 0.0f, 0.0f);
    rotation = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
    scale = FVector(1.0f, 1.0f, 1.0f);
}

void UVK::MeshComponentRaw::render(glm::mat4& projection, Camera& camera)
{
    mat = glm::mat4(1.0f);
    shader.useShader();

    uniformModel = shader.getModelLocation();
    uniformProjection = shader.getProjectionLocation();
    uniformView = shader.getViewLocation();

    Math::translate(mat, translation);
    Math::rotate(mat, rotation);
    Math::scale(mat, scale);
    if (!global.bUsesVulkan)
    {
        glUniformMatrix4fv((int)uniformModel, 1, GL_FALSE, glm::value_ptr(mat));
        glUniformMatrix4fv((int)uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv((int)uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrixRH()));
        mesh.render();
    }
}

void UVK::MeshComponentRaw::clearMesh()
{
    mesh.clear();
    shader.clearShader();

    index.clear();
    vertex.clear();
}