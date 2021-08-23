// VKMesh.hpp
// Last update 16/8/2021 by Madman10K
#pragma once
#include <Core/Types.hpp>
//#include <Core.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

namespace UVK
{
    class VKDevice;

    struct VKVertex
    {
        VKVertex() = default;
        VKVertex(FVector4 l, FVector4 c)
            : loc(l), colour(c)
        {
        }

        FVector4 loc{};
        FVector4 colour{};
    };

    /**
     * @brief Vulkan specific mesh class
     */
    class VKMesh
    {
    public:
        VKMesh() = default;
        VKMesh(VKDevice* dev, VkQueue& transQueue, VkCommandPool& transCommandPool, std::vector<VKVertex> vert, std::vector<uint32_t> index, VkPipelineLayout& pipelineL);

        void create();
        void render(const std::vector<VkCommandBuffer>& commandbuffers, const int& index, const std::vector<VkDescriptorSet>& descriptorSets);
        void clear();

        VkBuffer& data();
    private:
        VKDevice* device;
        VkPipelineLayout* pipelineLayout;
        VkBuffer vertexBuffer{};
        VkBuffer indexBuffer{};
        VkDeviceMemory deviceMemory{};
        VkDeviceMemory indexMemory{};
        VkQueue* transferQueue = nullptr;
        VkCommandPool* transferCommandPool;

        std::vector<VKVertex> vertices;
        std::vector<uint32_t> indices;
    };
}
