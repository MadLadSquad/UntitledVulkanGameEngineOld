#pragma once
#include "Renderer/EditorUI/Editor.hpp"

namespace UVK
{
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
        friend class Renderer;

        void run() noexcept;
        Editor ed;
        UVK::String colTheme;
#ifndef __APPLE__

#endif
    };
}
