// UI.hpp
// Last update 30/6/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    class UI
    {
    public:
        UI() = default;

        void addEvent(const std::function<void(void)>& func);
        void addEventImgui(const std::function<void(void)>& func);
    private:
        friend class GLPipeline;
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