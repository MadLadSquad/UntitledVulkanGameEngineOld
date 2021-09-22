// MeshComponentRaw.hpp
// Last update 22/9/2021 by Madman10K
#pragma once
#include <glm/gtx/quaternion.hpp>
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <Renderer/Camera/Camera.hpp>
#include <Renderer/Vulkan/Components/VKMesh.hpp>
#include <Renderer/Vulkan/Components/VKStructs.hpp>

namespace UVK
{
    struct CoreComponent;

    /**
     * @brief A mesh component used for debugging
     */
    struct MeshComponentRaw
    {
        void createMesh(UVK::Actor* currentActor, GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, UVK::String vertexShader, UVK::String fragmentShader, ShaderImportType type);
        void render(glm::mat4& projection, Camera& camera);
        void clearMesh();

        glm::mat4 mat;

        std::vector<uint32_t> index;
        std::vector<float> vertex;
        UVK::String fShader;
        UVK::String vShader;

        ShaderImportType impType;
    private:
        UVK::CoreComponent* core = nullptr;
        Actor* actor = nullptr;

        GLuint uniformModel = 0;
        GLuint uniformProjection = 0;
        GLuint uniformView = 0;

        GLMesh mesh;
        GLShader shader;
    };

    struct MeshComponentRawVK
    {
        void start(UVK::Actor* currentActor, UVK::VKDevice& device, VkQueue& transQueue, VkCommandPool& transCommandPool, const std::vector<VKVertex>& vert, const std::vector<uint32_t>& index);
        void render(const std::vector<VkCommandBuffer>& commandBuffers, const int32_t& index);
        void destroy();

        glm::mat4 mat;
    private:
        UVK::CoreComponent* core = nullptr;
        Actor* actor = nullptr;
        VKMesh mesh;
    };
}