// EditorModule.hpp
// Last update 10/9/2021 by Madman10K
#pragma once
#include <functional>
#include <vector>

namespace UVK
{
    class Actor;

    class EditorModuleManager
    {
    public:
        EditorModuleManager() = default;
        EditorModuleManager(const EditorModuleManager& mod) = delete;
        void operator=(EditorModuleManager const&) = delete;

        void addDetailsPanelModule(const std::function<void(Actor* actor)>& func);
        void addToolsModule(const std::function<void(void)>& func);
        void addIndependentModule(const std::function<void(void)>& func);
        void addTopBar(const std::function<void(void)>& func);
        void addTitleBar(const std::function<void(void)>& func);

        void renderDetailsPanelModules(Actor* actor);
        void renderToolsModule();
        void renderIndependentModule();
        void renderTopBar();
        void renderTitleBar();
    private:
        std::vector<std::function<void(Actor* actor)>> detailsPanelModules;
        std::vector<std::function<void(void)>> toolsModules;
        std::vector<std::function<void(void)>> independentModules;
        std::vector<std::function<void(void)>> topBarModules;
        std::vector<std::function<void(void)>> titleBarModules;
    };
}