// SceneHierarchy.hpp
// Last update 18/2/2022 by Madman10K
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
    bool display(UVK::Actor& selectedEntity, int& entNum, bool& bShow, std::vector<UVK::EditorFolder>& folders, const bool& bReset = false);

    UVK::Actor duplicateEntity(UVK::Actor& currentPopupEntity, const bool& bDrawHighlighted, const bool& nopop = true, UVK::EditorFolder* folder = nullptr);
    void duplicateFolder(std::vector<UVK::EditorFolder>& folders, UVK::EditorFolder* folder, const bool& bDrawHighlighted, const bool& nopop = true);
}
#endif