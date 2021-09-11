// EditorModules.hpp
// Last update 10/9/2021 by Madman10K
#pragma once
#include <functional>

namespace UVK
{
    class Actor;

    class EditorModules
    {
    public:
        EditorModules() = delete;
        EditorModules(const EditorModules&) = delete;
        void operator=(EditorModules const&) = delete;

        static void addDetailsPanelModule(const std::function<void(Actor* actor)>& func);
        static void addToolsModule(const std::function<void(void)>& func);
        static void addIndependentModule(const std::function<void(void)>& func);
        static void addTopBar(const std::function<void(void)>& func);
        static void addTitleBar(const std::function<void(void)>& func);
    };
}