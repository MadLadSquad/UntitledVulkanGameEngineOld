#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include "Core/Assets/Asset.hpp"
#include <imgui.h>
#include <Renderer/Textures/Texture.hpp>
#include <Core/Global.hpp>

namespace AssetSlot
{
    void assetSlotBegin(UVK::Texture& thumbnail, const int32_t& id, const std::function<void(void)>& function) noexcept;
    void assetSlotEnd() noexcept;

    void displayTexture(int32_t id, UVK::Texture* asset, std::string& name) noexcept;
    void displayAudio(int32_t id, UVK::Texture* asset, std::string& name) noexcept;
    void displayShaders(int32_t id, UVK::Texture* asset, std::string& name) noexcept;
    void displayVideo(int32_t id, UVK::Texture* asset, std::string& name) noexcept;
    void displayFont(int32_t id, UVK::Texture* asset, std::string& name) noexcept;
    void displayModel(int32_t id, UVK::Texture* asset, std::string& name) noexcept;
}
#endif