#pragma once
#include "Device.hpp"

namespace UVK
{
    class VKMesh
    {
    public:
        VKMesh() = default;
        VKMesh(VKDevice& dev, std::vector<VKVertex> vertices) noexcept;
        void destroyVertexBuffer() noexcept;

        [[nodiscard]] const size_t& vertexCount() const noexcept;
        VkBuffer& getVertexBuffer() noexcept;
    private:
        VKDevice* device = nullptr;
        VkBuffer vertexBuffer;
        VkDeviceMemory deviceMemory;
        size_t vertexNum;

        void createVertexBuffer(std::vector<VKVertex>& vertices) noexcept;


        uint32_t findMemoryTypeIndex(uint32_t allowedTypes, VkMemoryPropertyFlags properties);
    };
}