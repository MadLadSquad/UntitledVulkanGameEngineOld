#include "EditorModule.hpp"

#ifndef PRODUCTION
void UVK::EditorModuleManager::addDetailsPanelModule(const std::function<void(Actor*, bool&)>& func) noexcept
{
    detailsPanelModules.emplace_back(func);
}

void UVK::EditorModuleManager::addToolsModule(const std::function<void(const UVK::CurrentToolType&, bool&)>& func) noexcept
{
    toolsModules.emplace_back(func);
}

void UVK::EditorModuleManager::addIndependentModule(const UVK::IndependentModuleData& func) noexcept
{
    independentModules.emplace_back(func);
}

void UVK::EditorModuleManager::renderDetailsPanelModules(UVK::Actor* actor, bool& bReturn) const noexcept
{
    for (auto& a : detailsPanelModules)
        a(actor, bReturn);
}

void UVK::EditorModuleManager::renderToolsModule(const CurrentToolType& type, bool& bReturn) const noexcept
{
    for (auto& a : toolsModules)
        a(type, bReturn);
}

void UVK::EditorModuleManager::renderIndependentModule(bool& bReturn) noexcept
{
    for (auto& a : independentModules)
        if (a.bEnabled)
            a.func(a.name, a.bEnabled, bReturn);
}

void UVK::EditorModuleManager::addTopBar(const std::function<void(bool&)>& func) noexcept
{
    topBarModules.emplace_back(func);
}

void UVK::EditorModuleManager::renderTopBar(bool& bReturn) const noexcept
{
    for (auto& a : topBarModules)
        a(bReturn);
}

const std::vector<std::function<void(const UVK::CurrentToolType&, bool&)>>& UVK::EditorModuleManager::getToolsModules() const noexcept
{
    return toolsModules;
}

const std::vector<std::function<void(UVK::Actor* actor, bool&)>>& UVK::EditorModuleManager::getDetailsPanelModules() const noexcept
{
    return detailsPanelModules;
}

std::vector<UVK::IndependentModuleData>& UVK::EditorModuleManager::getIndependentModules() noexcept
{
    return independentModules;
}

const std::vector<std::function<void(bool&)>>& UVK::EditorModuleManager::getTopBarModules() const noexcept
{
    return topBarModules;
}
#else
void UVK::EditorModuleManager::addDetailsPanelModule(const std::function<void(Actor*, bool&)>& func) noexcept
{
}

void UVK::EditorModuleManager::addToolsModule(const std::function<void(const UVK::CurrentToolType&, bool&)>& func) noexcept
{
}

void UVK::EditorModuleManager::addIndependentModule(const UVK::IndependentModuleData& func) noexcept
{
}

void UVK::EditorModuleManager::renderDetailsPanelModules(UVK::Actor* actor, bool& bReturn) const noexcept
{
}

void UVK::EditorModuleManager::renderToolsModule(const CurrentToolType& type, bool& bReturn) const noexcept
{
}

void UVK::EditorModuleManager::renderIndependentModule(bool& bReturn) noexcept
{
}

void UVK::EditorModuleManager::addTopBar(const std::function<void(bool&)>& func) noexcept
{
}

void UVK::EditorModuleManager::renderTopBar(bool& bReturn) const noexcept
{
}

const std::vector<std::function<void(const UVK::CurrentToolType&, bool&)>>& UVK::EditorModuleManager::getToolsModules() const noexcept
{
}

const std::vector<std::function<void(UVK::Actor* actor, bool&)>>& UVK::EditorModuleManager::getDetailsPanelModules() const noexcept
{
}

std::vector<UVK::IndependentModuleData>& UVK::EditorModuleManager::getIndependentModules() noexcept
{
}

const std::vector<std::function<void(bool&)>>& UVK::EditorModuleManager::getTopBarModules() const noexcept
{
}
#endif