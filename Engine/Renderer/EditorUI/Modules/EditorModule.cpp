// EditorModule.cpp
// Last update 10/9/2021 by Madman10K
#include "EditorModule.hpp"

void UVK::EditorModuleManager::addDetailsPanelModule(const std::function<void(Actor*)>& func)
{
    detailsPanelModules.emplace_back(func);
}

void UVK::EditorModuleManager::addToolsModule(const std::function<void(void)>& func)
{
    toolsModules.emplace_back(func);
}

void UVK::EditorModuleManager::addIndependentModule(const std::function<void(void)>& func)
{
    independentModules.emplace_back(func);
}

void UVK::EditorModuleManager::renderDetailsPanelModules(UVK::Actor* actor)
{
    for (auto& a : detailsPanelModules)
    {
        a(actor);
    }
}

void UVK::EditorModuleManager::renderToolsModule()
{
    for (auto& a : toolsModules)
    {
        a();
    }
}

void UVK::EditorModuleManager::renderIndependentModule()
{
    for (auto& a : independentModules)
    {
        a();
    }
}

void UVK::EditorModuleManager::addTopBar(const std::function<void(void)>& func)
{
    topBarModules.emplace_back(func);
}

void UVK::EditorModuleManager::addTitleBar(const std::function<void(void)>& func)
{
    titleBarModules.emplace_back(func);
}

void UVK::EditorModuleManager::renderTopBar()
{
    for (auto& a : topBarModules)
    {
        a();
    }
}

void UVK::EditorModuleManager::renderTitleBar()
{
    for (auto& a : titleBarModules)
    {
        a();
    }
}
