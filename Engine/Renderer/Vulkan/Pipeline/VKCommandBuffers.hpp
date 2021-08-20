// VKCommandBuffer.hpp
// Last update 16/8/2021 by Madman10K
#pragma once
#ifndef __APPLE__
#include <vulkan/vulkan.h>
#include <vector>
#include <Renderer/Vulkan/Components/VKFramebuffer.hpp>

namespace UVK
{
    class Device;
    class VKGraphicsPipeline;
    class VKMesh;

    class VKCommandBuffers
    {
    public:
        VKCommandBuffers() = default;
        VKCommandBuffers(Device* dev, std::vector<VKFramebuffer>& framebuf, VkPipeline* gp, VkRenderPass* rp);

        void createCommandPool();
        void destroyCommandPool();

        void createCommandbuffers();
        void recordCommands(VKMesh& mesh);

        VkCommandPool& getCommandPool();
    private:
        friend class VKDraw;

        Device* device = nullptr;
        VkCommandPool commandPool{};
        VkPipeline* graphicsPipeline = nullptr;
        VkRenderPass* renderPass = nullptr;

        std::vector<VkCommandBuffer> commandbuffers;
        std::vector<VKFramebuffer>* framebuffers = nullptr;
    };
}
#endif