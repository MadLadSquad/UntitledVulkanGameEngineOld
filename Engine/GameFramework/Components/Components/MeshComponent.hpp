#pragma once
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <Renderer/Camera/Camera.hpp>

namespace UVK
{
    /**
     * @brief A simple mesh component
     */
    struct UVK_PUBLIC_API MeshComponent
    {
        void createMesh(UVK::String modelLocation, UVK::String vertexShader, UVK::String fragmentShader, ShaderImportType type) noexcept;
        void render(glm::mat4 projection, Camera& camera) noexcept;
        void clearMesh() noexcept;

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