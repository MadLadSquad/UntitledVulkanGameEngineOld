// MeshComponent.hpp
// Last update 17/7/2021 by Madman10K
#pragma once
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <Renderer/Camera/Camera.hpp>

namespace UVK
{
    /**
     * @brief A simple mesh component
     */
    struct MeshComponent
    {
        void createMesh(UVK::String modelLocation, UVK::String vertexShader, UVK::String fragmentShader, ShaderImportType type);
        void render(glm::mat4 projection, Camera& camera);
        void clearMesh();

        glm::mat4 mat;

        FVector rotation;
        FVector translation;
        FVector scale;

        UVK::String fShader;
        UVK::String vShader;

        ShaderImportType impType;
    private:
        uint32_t uniformModel = 0;
        uint32_t uniformProjection = 0;
        uint32_t uniformView = 0;

        GLMesh mesh;
        GLShader shader;
    };
}