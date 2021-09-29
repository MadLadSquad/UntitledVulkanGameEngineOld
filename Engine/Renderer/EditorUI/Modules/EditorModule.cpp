// EditorModule.cpp
// Last update 13/9/2021 by Madman10K
#include "EditorModule.hpp"

#ifndef PRODUCTION
void UVK::EditorModuleManager::addDetailsPanelModule(const std::function<void(Actor*)>& func)
{
    detailsPanelModules.emplace_back(func);
}

void UVK::EditorModuleManager::addToolsModule(const std::function<void(const UVK::CurrentToolType&)>& func)
{
    toolsModules.emplace_back(func);
}

void UVK::EditorModuleManager::addIndependentModule(const UVK::IndependentModuleData& func)
{
    independentModules.emplace_back(func);
}

void UVK::EditorModuleManager::renderDetailsPanelModules(UVK::Actor* actor) const
{
    for (auto& a : detailsPanelModules)
    {
        a(actor);
    }
}

void UVK::EditorModuleManager::renderToolsModule(const CurrentToolType& type) const
{
    for (auto& a : toolsModules)
    {
        a(type);
    }
}

void UVK::EditorModuleManager::renderIndependentModule()
{
    for (auto& a : independentModules)
    {
        if (a.bEnabled)
        {
            a.func(a.name, a.bEnabled);
        }
    }
}

void UVK::EditorModuleManager::addTopBar(const std::function<void(void)>& func)
{
    topBarModules.emplace_back(func);
}

void UVK::EditorModuleManager::renderTopBar() const
{
    for (auto& a : topBarModules)
    {
        a();
    }
}

const std::vector<std::function<void(const UVK::CurrentToolType&)>>& UVK::EditorModuleManager::getToolsModules() const
{
    return toolsModules;
}

const std::vector<std::function<void(UVK::Actor* actor)>>& UVK::EditorModuleManager::getDetailsPanelModules() const
{
    return detailsPanelModules;
}

std::vector<UVK::IndependentModuleData>& UVK::EditorModuleManager::getIndependentModules()
{
    return independentModules;
}

const std::vector<std::function<void()>>& UVK::EditorModuleManager::getTopBarModules() const
{
    return topBarModules;
}
#else
void UVK::EditorModuleManager::addDetailsPanelModule(const std::function<void(Actor*)>& func)
{
}

void UVK::EditorModuleManager::addToolsModule(const std::function<void(const UVK::CurrentToolType&)>& func)
{
}

void UVK::EditorModuleManager::addIndependentModule(const UVK::IndependentModuleData& func)
{
}

void UVK::EditorModuleManager::renderDetailsPanelModules(UVK::Actor* actor) const
{
}

void UVK::EditorModuleManager::renderToolsModule(const CurrentToolType& type) const
{
}

void UVK::EditorModuleManager::renderIndependentModule()
{
}

void UVK::EditorModuleManager::addTopBar(const std::function<void(void)>& func)
{
}

void UVK::EditorModuleManager::renderTopBar() const
{
}

const std::vector<std::function<void(const UVK::CurrentToolType&)>>& UVK::EditorModuleManager::getToolsModules() const
{
}

const std::vector<std::function<void(UVK::Actor* actor)>>& UVK::EditorModuleManager::getDetailsPanelModules() const
{
}

std::vector<UVK::IndependentModuleData>& UVK::EditorModuleManager::getIndependentModules()
{
}

const std::vector<std::function<void()>>& UVK::EditorModuleManager::getTopBarModules() const
{
}
#endif