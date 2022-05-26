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
    class Actor;
    /**
     * @brief A simple mesh component that is fed data trough a file
     */
    struct UVK_PUBLIC_API MeshComponent
    {
        MeshComponent() = default;
        void create(String location, VKDevice& dev, Commands& cmd, VKDescriptors& desc, UVK::CoreComponent& core) noexcept;
        void update(size_t index, uint32_t currentImage, GraphicsPipeline& pipeline) noexcept;
        void destroy() noexcept;

        FVector translationOffset = FVector(0.0f, 0.0f, 0.0f);
        FVector rotationOffset = FVector(0.0f, 0.0f, 0.0f);
        FVector scaleOffset = FVector(0.0f, 0.0f, 0.0f);

        FVector4 hue = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::mat4 model = glm::mat4(1.0f);
    private:
        friend class Level;

        void saveToLevel(YAML::Emitter& out) noexcept;
        static void openFromLevel(UVK::Actor& act, const YAML::Node& entity) noexcept;

        UVK::CoreComponent* coreCache = nullptr;

        void loadNode(aiNode* node, const aiScene* scene) noexcept;
        void loadMesh(aiMesh* mesh, const aiScene* scene) noexcept;

        VKDevice* device = nullptr;
        Commands* commands = nullptr;
        VKDescriptors* descriptors = nullptr;

        FString loc;

        std::vector<Texture> textures{};
        std::vector<VKMesh> meshes{};
        std::vector<size_t> matids{};
    };
}