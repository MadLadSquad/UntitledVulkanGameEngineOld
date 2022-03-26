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
    UVK::Actor addEntity(int& entNum) noexcept;
    void destroyEntity(UVK::Actor& selectedEntity) noexcept;
    bool display(UVK::Actor& selectedEntity, int& entNum, bool& bShow, std::vector<UVK::EditorFolder>& folders, const bool& bReset = false) noexcept;

    UVK::Actor duplicateEntity(UVK::Actor& currentPopupEntity, const bool& bDrawHighlighted, const bool& nopop = true, UVK::EditorFolder* folder = nullptr) noexcept;
    void duplicateFolder(std::vector<UVK::EditorFolder>& folders, UVK::EditorFolder* folder, const bool& bDrawHighlighted, const bool& nopop = true) noexcept;
}
#endif