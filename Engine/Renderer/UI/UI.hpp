// UI.hpp
// Last update 30/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <utility>

namespace UVK
{
    class UI
    {
    public:
        UI() = default;
        explicit UI(std::string filename)
            : file(std::move(filename)) {}

        void init();
        void update(const std::string& fname);
        static void clean();

        static void beginFrame();
    private:
        std::string file;
        std::string savedBuffer;
        bool rerender = false;

        void renderUI();
        void cacheScaffold();
    };
}