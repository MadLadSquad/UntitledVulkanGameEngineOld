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
    void assetSlotBegin(UVK::Texture& thumbnail, const int32_t& id, const std::function<void(void)>& function);
    void assetSlotEnd();

    void displayTexture(int32_t id, UVK::Texture* asset, std::string& name);
    void displayAudio(int32_t id, UVK::Texture* asset, std::string& name);
    void displayShaders(int32_t id, UVK::Texture* asset, std::string& name);
    void displayVideo(int32_t id, UVK::Texture* asset, std::string& name);
    void displayFont(int32_t id, UVK::Texture* asset, std::string& name);
    void displayModel(int32_t id, UVK::Texture* asset, std::string& name);
}
#endif