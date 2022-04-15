#pragma once
#include "Renderer/EditorUI/Editor.hpp"
#include "Components/Instance.hpp"
#include "Components/Device.hpp"
#include "Components/Swapchain.hpp"
#include "Components/GraphicsPipeline.hpp"
#include "Components/Descriptors.hpp"
#include "Components/Depth.hpp"

namespace UVK
{
    struct InternalRendererComponents
    {
        void create() noexcept;
        void destroy() noexcept;
        void recreate() noexcept;

        VKInstance instance;
        VKDevice device;
        Swapchain swapchain;
        VKDescriptors descriptors;
        VKDepthBuffer depthBuffer;
        GraphicsPipeline pipeline;
        VKResources resources;
        Commands commands;
    };

    /**
     * @brief The vulkan specific renderer class
     */
    class UVK_PUBLIC_API VulkanRenderer
    {
    public:
        VulkanRenderer() = default;
        VulkanRenderer(const VulkanRenderer&) = delete;
        void operator=(VulkanRenderer const&) = delete;
    private:
        static void updateEvents(double deltaTime) noexcept;
        void beginEvents() noexcept;
        static void destroyEvents() noexcept;

        friend class Renderer;

        void run() noexcept;
        Editor ed;
        UVK::String colTheme;

        InternalRendererComponents renderer{};
#ifndef __APPLE__

#endif
    };
}
