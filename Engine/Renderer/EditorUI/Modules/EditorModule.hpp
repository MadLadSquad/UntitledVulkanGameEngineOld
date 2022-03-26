#pragma once
#include <functional>
#include <vector>
#include <Core/Defines.hpp>

namespace UVK
{
    class Actor;

    enum CurrentToolType
    {
        CURRENT_TOOL_TYPE_USEFUL_OBJECTS,
        CURRENT_TOOL_TYPE_TERRAIN_EDITOR,
        CURRENT_TOOL_TYPE_CUSTOM
    };

    struct IndependentModuleData
    {
        bool bEnabled;
        std::function<void(const char*, bool&, bool&)> func;
        const char* name;
    };

    class UVK_PUBLIC_API EditorModuleManager
    {
    public:
        EditorModuleManager() = default;
        EditorModuleManager(const EditorModuleManager& mod) = delete;
        void operator=(EditorModuleManager const&) = delete;

        void addDetailsPanelModule(const std::function<void(Actor* actor, bool&)>& func) noexcept;
        void addToolsModule(const std::function<void(const CurrentToolType&, bool&)>& func) noexcept;
        void addIndependentModule(const UVK::IndependentModuleData& func) noexcept;
        void addTopBar(const std::function<void(bool&)>& func) noexcept;

        void renderDetailsPanelModules(Actor* actor, bool& bReturn) const noexcept;
        void renderToolsModule(const CurrentToolType& type, bool& bReturn) const noexcept;
        void renderIndependentModule(bool& bReturn) noexcept;
        void renderTopBar(bool& bReturn) const noexcept;

        [[nodiscard]] const std::vector<std::function<void(const UVK::CurrentToolType&, bool&)>>& getToolsModules() const noexcept;
        [[nodiscard]] const std::vector<std::function<void(Actor* actor, bool&)>>& getDetailsPanelModules() const noexcept;
        std::vector<IndependentModuleData>& getIndependentModules() noexcept;
        [[nodiscard]] const std::vector<std::function<void(bool&)>>& getTopBarModules() const noexcept;
    private:
        std::vector<std::function<void(Actor* actor, bool&)>> detailsPanelModules;
        std::vector<std::function<void(const CurrentToolType&, bool&)>> toolsModules;
        std::vector<IndependentModuleData> independentModules;
        std::vector<std::function<void(bool&)>> topBarModules;
    };
}