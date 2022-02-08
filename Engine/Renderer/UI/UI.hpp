// UI.hpp
// Last update 7/2/2022 by Madman10K
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

        void addEvent(const std::function<void(void)>& func);
        void addEventImgui(const std::function<void(void)>& func);
    private:
        friend class GLPipeline;
        friend class VulkanRenderer;
        friend class Level;

        void init();
        void update();
        static void clean();
        void clear();
        static void beginFrame();

        std::vector<std::function<void(void)>> eventArr;
        std::vector<std::function<void(void)>> eventArrImGui;
        void renderUI();
    };
}