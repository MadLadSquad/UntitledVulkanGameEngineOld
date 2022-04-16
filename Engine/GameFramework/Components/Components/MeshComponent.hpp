#pragma once
#include <Renderer/Camera/Camera.hpp>
#include "Renderer/Vulkan/Components/Device.hpp"
#include "Renderer/Vulkan/Components/Commands.hpp"
#include <vector>
#include <Core/Defines.hpp>
#include <Core/Types.hpp>
#include <Renderer/Textures/Texture.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace UVK
{
    /**
     * @brief A simple mesh component
     */
    struct UVK_PUBLIC_API MeshComponent
    {
        MeshComponent() = default;
        void create(String location, VKDevice& dev, Commands& cmd, VKDescriptors& desc) noexcept;
        void update(size_t index, uint32_t currentImage, GraphicsPipeline& pipeline) noexcept;
        void destroy() noexcept;

        FVector translation = FVector(0.0f, 0.0f, 0.0f);
        FVector rotation = FVector(0.0f, 0.0f, 0.0f);
        FVector scale = FVector(1.0f, 1.0f, 1.0f);

        FVector4 hue = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
    private:
        void loadNode(aiNode* node, const aiScene* scene) noexcept;
        void loadMesh(aiMesh* mesh, const aiScene* scene) noexcept;

        glm::mat4 model = glm::mat4(1.0f);

        VKDevice* device = nullptr;
        Commands* commands = nullptr;
        VKDescriptors* descriptors = nullptr;

        std::vector<Texture> textures{};
        std::vector<VKMesh> meshes{};
        std::vector<size_t> matids{};
    };
}