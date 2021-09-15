// EditorModules.hpp
// Last update 13/9/2021 by Madman10K
#include "EditorModuleInterface.hpp"
#include <Core/Global.hpp>
#include <Renderer/EditorUI/Editor.hpp>

void UVK::EditorModules::addDetailsPanelModule(const std::function<void(Actor*)>& func)
{
    global.instance->editor->moduleManager.addDetailsPanelModule(func);
}

void UVK::EditorModules::addToolsModule(const std::function<void(const UVK::CurrentToolType&)>& func)
{
    global.instance->editor->moduleManager.addToolsModule(func);
}

void UVK::EditorModules::addIndependentModule(const UVK::IndependentModuleData& func)
{
    global.instance->editor->moduleManager.addIndependentModule(func);
}

void UVK::EditorModules::addTopBar(const std::function<void(void)>& func)
{
    global.instance->editor->moduleManager.addTopBar(func);
}