#pragma once
#include <Renderer/EditorUI/Modules/EditorModule.hpp>

namespace UVK
{
    class Actor;
    struct IndependentModuleData;

    // A class to handle easy interfacing with the editor modules system
    class UVK_PUBLIC_API EditorModules
    {
    public:
        EditorModules() = delete;
        EditorModules(const EditorModules&) = delete;
        void operator=(EditorModules const&) = delete;

        static void addDetailsPanelModule(const std::function<void(Actor* actor, bool&)>& func) noexcept;
        static void addToolsModule(const std::function<void(const UVK::CurrentToolType&, bool&)>& func) noexcept;
        static void addIndependentModule(const UVK::IndependentModuleData& func) noexcept;
        static void addTopBar(const std::function<void(bool&)>& func) noexcept;
    };
}