// SceneHierarchy.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include <iostream>
#include "Renderer/EditorUI/Editor.hpp"

namespace UVK
{
    class Actor;
}
/**
 * @brief The scene hierarchy widget creates, manages, destroys entities
 */
namespace SceneHierarchy
{
    UVK::Actor addEntity(int& entNum);
    void destroyEntity(UVK::Actor& selectedEntity);
    bool display(UVK::Actor& selectedEntity, std::string& entAppend, int& entNum, bool& bShow, std::vector<UVK::Editor::Folder>& folders, const bool& bReset = false);
    void duplicateFolder(UVK::Editor::Folder* currentPopupFolder, std::vector<UVK::Editor::Folder>& folders);
    void duplicateEntity(UVK::Actor& currentPopupEntity, const bool& bDrawHighlighted);
}
#endif