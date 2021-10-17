// EditorModule.hpp
// Last update 13/9/2021 by Madman10K
#pragma once
#include <functional>
#include <vector>

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

    class EditorModuleManager
    {
    public:
        EditorModuleManager() = default;
        EditorModuleManager(const EditorModuleManager& mod) = delete;
        void operator=(EditorModuleManager const&) = delete;

        void addDetailsPanelModule(const std::function<void(Actor* actor, bool&)>& func);
        void addToolsModule(const std::function<void(const CurrentToolType&, bool&)>& func);
        void addIndependentModule(const UVK::IndependentModuleData& func);
        void addTopBar(const std::function<void(bool&)>& func);

        void renderDetailsPanelModules(Actor* actor, bool& bReturn) const;
        void renderToolsModule(const CurrentToolType& type, bool& bReturn) const;
        void renderIndependentModule(bool& bReturn);
        void renderTopBar(bool& bReturn) const;

        [[nodiscard]] const std::vector<std::function<void(const UVK::CurrentToolType&, bool&)>>& getToolsModules() const;
        [[nodiscard]] const std::vector<std::function<void(Actor* actor, bool&)>>& getDetailsPanelModules() const;
        std::vector<IndependentModuleData>& getIndependentModules();
        [[nodiscard]] const std::vector<std::function<void(bool&)>>& getTopBarModules() const;
    private:
        std::vector<std::function<void(Actor* actor, bool&)>> detailsPanelModules;
        std::vector<std::function<void(const CurrentToolType&, bool&)>> toolsModules;
        std::vector<IndependentModuleData> independentModules;
        std::vector<std::function<void(bool&)>> topBarModules;
    };
}