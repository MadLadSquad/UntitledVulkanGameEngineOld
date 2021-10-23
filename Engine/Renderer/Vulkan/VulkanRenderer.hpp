// VulkanRenderer.hpp
// Last update 16/8/2021 by Madman10K
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
    /**
     * @brief The vulkan specific renderer class
     */
    class VulkanRenderer
    {
    public:
        VulkanRenderer() = default;
        VulkanRenderer(const VulkanRenderer&) = delete;
        void operator=(VulkanRenderer const&) = delete;
    private:
        friend class Renderer;

        void run();

        VKPipeline pipeline;
#ifndef __APPLE__

#endif
    };
}
