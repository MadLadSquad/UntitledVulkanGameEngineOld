#pragma once
#include <glm/gtx/quaternion.hpp>
#include <Renderer/Vulkan/Components/VKMesh.hpp>
#include <Renderer/Vulkan/Components/Commands.hpp>
#include <Renderer/Camera/Camera.hpp>

namespace UVK
{
    struct CoreComponent;
    class Actor;

    /**
     * @brief A mesh component used for debugging
     */
    struct UVK_PUBLIC_API MeshComponentRaw
    {
    public:
        void create(std::vector<VKVertex> vertices, std::vector<uint32_t> indices, VKDevice& dev, Commands& cmd);
        void update(size_t index, uint32_t currentImage, GraphicsPipeline& pipeline, VKDescriptors& descriptors);
        void destroy();

        FVector translation = FVector(0.0f, 0.0f, 0.0f);
        FVector rotation = FVector(0.0f, 0.0f, 0.0f);
        FVector scale = FVector(1.0f, 1.0f, 1.0f);
    private:
        VKDevice* device = nullptr;
        Commands* commands = nullptr;

        VKMesh mesh{};
    };
}