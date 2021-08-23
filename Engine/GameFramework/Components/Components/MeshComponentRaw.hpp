// MeshComponentRaw.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <glm/gtx/quaternion.hpp>
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <Renderer/Camera/Camera.hpp>
#include <Renderer/Vulkan/Components/VKMesh.hpp>
#include <Renderer/Vulkan/Components/VKStructs.hpp>

namespace UVK
{
    /**
     * @brief A mesh component used for debugging
     */
    struct MeshComponentRaw
    {
        void createMesh(GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, UVK::String vertexShader, UVK::String fragmentShader, ShaderImportType type);
        void render(glm::mat4& projection, Camera& camera);
        void clearMesh();

        glm::mat4 mat;

        FVector rotation;
        FVector translation;
        FVector scale;

        std::vector<uint32_t> index;
        std::vector<float> vertex;
        UVK::String fShader;
        UVK::String vShader;

        ShaderImportType impType;
    private:
        GLuint uniformModel = 0;
        GLuint uniformProjection = 0;
        GLuint uniformView = 0;

        GLMesh mesh;
        GLShader shader;
    };

    struct MeshComponentRawVK
    {
        void start(UVK::VKDevice& device, VkQueue& transQueue, VkCommandPool& transCommandPool, const std::vector<VKVertex>& vert, const std::vector<uint32_t>& index);
        void render(const std::vector<VkCommandBuffer>& commandBuffers, const int32_t& index);
        void destroy();

        glm::mat4 mat;

        FVector rotation;
        FVector translation;
        FVector scale;
    private:
        VKMesh mesh;
    };
}