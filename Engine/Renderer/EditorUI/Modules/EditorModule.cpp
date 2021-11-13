// EditorModule.cpp
// Last update 13/9/2021 by Madman10K
#include "EditorModule.hpp"

#ifndef PRODUCTION
void UVK::EditorModuleManager::addDetailsPanelModule(const std::function<void(Actor*, bool&)>& func)
{
    detailsPanelModules.emplace_back(func);
}

void UVK::EditorModuleManager::addToolsModule(const std::function<void(const UVK::CurrentToolType&, bool&)>& func)
{
    toolsModules.emplace_back(func);
}

void UVK::EditorModuleManager::addIndependentModule(const UVK::IndependentModuleData& func)
{
    independentModules.emplace_back(func);
}

void UVK::EditorModuleManager::renderDetailsPanelModules(UVK::Actor* actor, bool& bReturn) const
{
    for (auto& a : detailsPanelModules)
        a(actor, bReturn);
}

void UVK::EditorModuleManager::renderToolsModule(const CurrentToolType& type, bool& bReturn) const
{
    for (auto& a : toolsModules)
        a(type, bReturn);
}

void UVK::EditorModuleManager::renderIndependentModule(bool& bReturn)
{
    for (auto& a : independentModules)
        if (a.bEnabled)
            a.func(a.name, a.bEnabled, bReturn);
}

void UVK::EditorModuleManager::addTopBar(const std::function<void(bool&)>& func)
{
    topBarModules.emplace_back(func);
}

void UVK::EditorModuleManager::renderTopBar(bool& bReturn) const
{
    for (auto& a : topBarModules)
        a(bReturn);
}

const std::vector<std::function<void(const UVK::CurrentToolType&, bool&)>>& UVK::EditorModuleManager::getToolsModules() const
{
    return toolsModules;
}

const std::vector<std::function<void(UVK::Actor* actor, bool&)>>& UVK::EditorModuleManager::getDetailsPanelModules() const
{
    return detailsPanelModules;
}

std::vector<UVK::IndependentModuleData>& UVK::EditorModuleManager::getIndependentModules()
{
    return independentModules;
}

const std::vector<std::function<void(bool&)>>& UVK::EditorModuleManager::getTopBarModules() const
{
    return topBarModules;
}
#else
void UVK::EditorModuleManager::addDetailsPanelModule(const std::function<void(Actor*, bool&)>& func)
{
}

void UVK::EditorModuleManager::addToolsModule(const std::function<void(const UVK::CurrentToolType&, bool&)>& func)
{
}

void UVK::EditorModuleManager::addIndependentModule(const UVK::IndependentModuleData& func)
{
}

void UVK::EditorModuleManager::renderDetailsPanelModules(UVK::Actor* actor, bool& bReturn) const
{
}

void UVK::EditorModuleManager::renderToolsModule(const CurrentToolType& type, bool& bReturn) const
{
}

void UVK::EditorModuleManager::renderIndependentModule(bool& bReturn)
{
}

void UVK::EditorModuleManager::addTopBar(const std::function<void(bool&)>& func)
{
}

void UVK::EditorModuleManager::renderTopBar(bool& bReturn) const
{
}

const std::vector<std::function<void(const UVK::CurrentToolType&, bool&)>>& UVK::EditorModuleManager::getToolsModules() const
{
}

const std::vector<std::function<void(UVK::Actor* actor, bool&)>>& UVK::EditorModuleManager::getDetailsPanelModules() const
{
}

std::vector<UVK::IndependentModuleData>& UVK::EditorModuleManager::getIndependentModules()
{
}

const std::vector<std::function<void(bool&)>>& UVK::EditorModuleManager::getTopBarModules() const
{
}
#endif