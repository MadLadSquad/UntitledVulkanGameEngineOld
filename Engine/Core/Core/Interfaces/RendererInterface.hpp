#pragma once
#include <Core/Defines.hpp>

namespace UVK
{
    class UVK_PUBLIC_API Renderer
    {
    public:
        Renderer(const Renderer&) = delete;
        void operator=(Renderer const&) = delete;

        // Will switch your renderer API, save the rendering settings and shut down the application
        static void switchRenderer() noexcept;

        // When V-Sync is off, in Vulkan we have 2 presentation modes that are going to be toggled by this boolean.
        // If the boolean is true we will render in 'VK_PRESENT_MODE_IMMEDIATE_KHR', but if it is false we will present
        // in 'VK_PRESENT_MODE_FIFO_RELAXED_KHR', this however depends on if the graphics card supports all 2 modes so
        // setting this boolean to true will not always result in the desired effect. You can read about what the
        // presentation modes do here:
        // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkPresentModeKHR.html#_description
        static bool& getImmediateRender() noexcept;
        static bool& getVSync() noexcept;
        static void saveSettings() noexcept;
        static uint32_t& msaaSampleCount() noexcept;
        static bool& sampleRateShading() noexcept;
        static float& sampleRateShadingMult() noexcept;
    };
}