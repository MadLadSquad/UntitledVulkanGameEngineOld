#pragma once
#include "Device.hpp"
#include "Buffer.hpp"

namespace UVK
{
    class VKMesh
    {
    public:
        VKMesh() = default;
        VKMesh(VKDevice& dev, VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<VKVertex> vertices, std::vector<uint32_t> indices) noexcept;
        void destroyVertexBuffer() noexcept;

        [[nodiscard]] const size_t& vertexCount() const noexcept;
        VKBuffer& getVertexBuffer() noexcept;
        VKBuffer& getIndexBuffer() noexcept;
        [[nodiscard]] const size_t& indexCount() const noexcept;

        Model model = { glm::mat4(1.0f) };
    private:
        VKDevice* device = nullptr;
        VKBuffer buffer{};
        size_t vertexNum = 0;
        VKBuffer indexBuffer{};
        size_t indexNum = 0;

        void createVertexBuffer(VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<VKVertex>& vertices, std::vector<uint32_t>& indices) noexcept;
    };
}