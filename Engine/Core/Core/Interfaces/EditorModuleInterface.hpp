// EditorModules.hpp
// Last update 13/9/2021 by Madman10K
#pragma once
#include <Renderer/EditorUI/Modules/EditorModule.hpp>

namespace UVK
{
    class Actor;
    struct IndependentModuleData;

    class EditorModules
    {
    public:
        EditorModules() = delete;
        EditorModules(const EditorModules&) = delete;
        void operator=(EditorModules const&) = delete;

        static void addDetailsPanelModule(const std::function<void(Actor* actor, bool&)>& func);
        static void addToolsModule(const std::function<void(const UVK::CurrentToolType&, bool&)>& func);
        static void addIndependentModule(const UVK::IndependentModuleData& func);
        static void addTopBar(const std::function<void(bool&)>& func);
    };
}