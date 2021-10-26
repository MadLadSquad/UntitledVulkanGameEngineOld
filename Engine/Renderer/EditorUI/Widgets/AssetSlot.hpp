// AssetSlot.hpp
// Last update 26/10/2021 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include "Core/Assets/Asset.hpp"
#include <imgui.h>
#include <Renderer/Textures/Texture.hpp>
#include <Core/Global.hpp>

namespace AssetSlot
{
    static void assetSlotBegin(UVK::Texture& thumbnail, int32_t id)
    {
        ImGui::Columns(2, nullptr, false);

        ImGui::SetColumnWidth(0, 66.0f);
        ImGui::Image((void*)(intptr_t)thumbnail.getImage(), { 50.0f, 50.0f });
        ImGui::NextColumn();
        ImGui::PushID(id);
    }

    static void assetSlotEnd()
    {
        ImGui::PopID();
        ImGui::NextColumn();
        ImGui::Columns(1);
    }

    static void displayTexture(int32_t id, UVK::Texture& thumbnail, UVK::Texture& remove, UVK::Texture* asset)//UVK::Asset<T>& asset, bool& bOpen)
    {
        assetSlotBegin(thumbnail, id);
        static std::string name = "None";

        if (ImGui::BeginCombo(static_cast<std::string>("##filename" + std::to_string(id)).c_str(), name.c_str()))
        {
            //for (auto& a : UVK::Assets::textures())
            //{
            //    if (ImGui::MenuItem(a.location.c_str()))
            //    {
            //        name = a.location;
            //    }
            //}
            ImGui::EndCombo();
        }
        
        if (ImGui::ImageButton((void*)(intptr_t)remove.getImage(), { 16.0f, 16.0f }))
        {
            asset = nullptr;
            name = "None";
        }

        assetSlotEnd();
    }
}
#endif