// VKDraw.hpp
// Last update 16/8/2021 by Madman10K
#pragma once
#ifndef __APPLE
#include <vulkan/vulkan.h>
#include <vector>
#include "VKCommandBuffers.hpp"

namespace UVK
{
    class Device;
    class VKSwapchain;
    class VKCommandBuffers;
    class VKMesh;

    class VKDraw
    {
    public:
        VKDraw() = default;
        VKDraw(Device* dev, VKSwapchain* sw, VKCommandBuffers* cmd);

        void createSynchronisation();
        void destroySynchronisasion();

        bool getNextImage(UVK::VKMesh& mesh1);
    private:
        int currentFrame = 0;
        Device* device;
        VKSwapchain* swapchain;
        VKCommandBuffers* commandBuffers;

        std::vector<VkSemaphore> imageAvailable;
        std::vector<VkSemaphore> finishedRendering;
        std::vector<VkFence> fences;
    };
}
#endif