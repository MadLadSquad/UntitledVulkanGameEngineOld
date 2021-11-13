// AssetSlot.hpp
// Last update 8/11/2021 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include "Core/Assets/Asset.hpp"
#include <imgui.h>
#include <Renderer/Textures/Texture.hpp>
#include <Core/Global.hpp>

namespace AssetSlot
{
    void assetSlotBegin(UVK::Texture& thumbnail, const int32_t& id);
    void assetSlotEnd();

    void displayTexture(int32_t id, UVK::Texture* asset);
    void displayAudio(int32_t id, UVK::Texture* asset);
    void displayShaders(int32_t id, UVK::Texture* asset);
    void displayVideo(int32_t id, UVK::Texture* asset);
    void displayFont(int32_t id, UVK::Texture* asset);
    void displayModel(int32_t id, UVK::Texture* asset);
}
#endif