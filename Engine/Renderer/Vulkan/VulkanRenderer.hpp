// VulkanRenderer.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "Components/VKStructs.hpp"
#include "Pipeline/VKPipeline.hpp"
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace UVK
{
    class VulkanRenderer
    {
    public:
        VulkanRenderer() = default;

        void run();
    private:
        void start();
        void render();
        void cleanup();

        VKPipeline pipeline;
#ifndef __APPLE__
        VkSurfaceFormatKHR findSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
#endif
    };
}
