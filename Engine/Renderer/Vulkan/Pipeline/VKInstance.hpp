// VulkanRenderer.cpp
// Last update 26/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __APPLE__
#include <vulkan/vulkan.h>

namespace UVK
{
    /**
     * @brief Manages a vulkan instance
     */
    class VKInstance
    {
    public:
        VKInstance() = default;

        void create();
        void destroy();

        VkInstance& getData()
        {
            return instance;
        }
    private:
        static bool checkExtensionSupport(std::vector<UVK::String>* extensions);

        VkInstance instance;
    };
}
#endif
