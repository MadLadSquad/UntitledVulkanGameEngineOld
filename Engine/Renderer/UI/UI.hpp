#pragma once
#include <Core.hpp>

namespace UVK
{
    class UVK_PUBLIC_API UIInternal
    {
    public:
        UIInternal() = default;
        UIInternal(const UIInternal&) = delete;
        void operator=(UIInternal const&) = delete;

        void addEvent(const std::function<void(void)>& func) noexcept;
        void addEventImgui(const std::function<void(void)>& func) noexcept;
    private:
        friend class GLPipeline;
        friend class VulkanRenderer;
        friend class Level;

        static void init() noexcept;
        void update() noexcept;
        static void clean() noexcept;
        void clear() noexcept;
        static void beginFrame() noexcept;

        std::vector<std::function<void(void)>> eventArr;
        std::vector<std::function<void(void)>> eventArrImGui;
        void renderUI() noexcept;
    };
}