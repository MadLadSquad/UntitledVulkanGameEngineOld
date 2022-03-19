// MeshComponentRaw.cpp
// Last update 21/12/2021 by Madman10K
#include <GL/glew.h>
#include "CoreComponent.hpp"
#include "MeshComponentRaw.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Actor.hpp"

void UVK::MeshComponentRaw::createMesh(UVK::Actor* currentActor, GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, UVK::String vertexShader, UVK::String fragmentShader, ShaderImportType type)
{
    fShader = fragmentShader;
    vShader = vertexShader;
    impType = type;
    actor = currentActor;

    for (int i = 0; i < indexNum; i++)
        index.push_back(indices[i]);
    for (int i = 0; i < vertexNum; i++)
        vertex.push_back(vertices[i]);

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

    core = &actor->get<CoreComponent>();
}

void UVK::MeshComponentRaw::render(Camera& camera)
{
    mat = glm::mat4(1.0f);
    shader.useShader();

    uniformModel = shader.getModelLocation();
    uniformProjection = shader.getProjectionLocation();
    uniformView = shader.getViewLocation();

    Math::translate(mat, core->translation);
    Math::rotate(mat, core->rotation);
    Math::scale(mat, core->scale);
    if (!global.bUsesVulkan)
    {
        glUniformMatrix4fv((int)uniformModel, 1, GL_FALSE, glm::value_ptr(mat));
        glUniformMatrix4fv((int)uniformProjection, 1, GL_FALSE, glm::value_ptr(camera.projection().data()));
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