// AssetSlot.cpp
// Last update 8/11/2021 by Madman10K
#include "AssetSlot.hpp"

#ifndef PRODUCTION
#include <Renderer/EditorUI/Editor.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>

void AssetSlot::assetSlotBegin(UVK::Texture& thumbnail, const int32_t& id)
{
    ImGui::Columns(2, nullptr, false);

    ImGui::SetColumnWidth(0, 66.0f);
    ImGui::Image((void*)(intptr_t)thumbnail.getImage(), { 50.0f, 50.0f });
    ImGui::NextColumn();
    ImGui::PushID(id);
}

void AssetSlot::assetSlotEnd()
{
    ImGui::PopID();
    ImGui::NextColumn();
    ImGui::Columns(1);
}

void AssetSlot::displayTexture(int32_t id, UVK::Texture* asset)
{
    UVK::EditorPointer editorPointer;

    assetSlotBegin(editorPointer.fsicons()[FS_ICON_IMAGE], id);
    static std::string name = "None";

    if (ImGui::BeginCombo(static_cast<std::string>("##filename" + std::to_string(id)).c_str(), name.c_str()))
    {
        for (auto& a : UVK::AssetManager::getAllAssetsOfType(UVK::ASSET_TYPE_TEXTURE))
        {
            if (ImGui::MenuItem((a.name + "##" + a.path).c_str()))
            {
                name = a.name;
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }

    assetSlotEnd();
}

void AssetSlot::displayAudio(int32_t id, UVK::Texture* asset)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_AUDIO], id);
    static std::string name = "None";

    if (ImGui::BeginCombo(static_cast<std::string>("##filename" + std::to_string(id)).c_str(), name.c_str()))
    {
        for (auto& a : UVK::AssetManager::getAllAssetsOfType(UVK::ASSET_TYPE_AUDIO))
        {
            if (ImGui::MenuItem((a.name + "##" + a.path).c_str()))
            {
                name = a.name;
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayFont(int32_t id, UVK::Texture* asset)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_FONT], id);
    static std::string name = "None";

    if (ImGui::BeginCombo(static_cast<std::string>("##filename" + std::to_string(id)).c_str(), name.c_str()))
    {
        for (auto& a : UVK::AssetManager::getAllAssetsOfType(UVK::ASSET_TYPE_FONT))
        {
            if (ImGui::MenuItem((a.name + "##" + a.path).c_str()))
            {
                name = a.name;
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayModel(int32_t id, UVK::Texture* asset)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_MODEL], id);
    static std::string name = "None";

    if (ImGui::BeginCombo(static_cast<std::string>("##filename" + std::to_string(id)).c_str(), name.c_str()))
    {
        for (auto& a : UVK::AssetManager::getAllAssetsOfType(UVK::ASSET_TYPE_MODEL))
        {
            if (ImGui::MenuItem((a.name + "##" + a.path).c_str()))
            {
                name = a.name;
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayShaders(int32_t id, UVK::Texture* asset)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_CODE], id);
    static std::string name = "None";

    if (ImGui::BeginCombo(static_cast<std::string>("##filename" + std::to_string(id)).c_str(), name.c_str()))
    {
        for (auto& a : UVK::AssetManager::getAllAssetsOfType(UVK::ASSET_TYPE_SHADER))
        {
            if (ImGui::MenuItem((a.name + "##" + a.path).c_str()))
            {
                name = a.name;
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayVideo(int32_t id, UVK::Texture* asset)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_VIDEO], id);
    static std::string name = "None";

    if (ImGui::BeginCombo(static_cast<std::string>("##filename" + std::to_string(id)).c_str(), name.c_str()))
    {
        for (auto& a : UVK::AssetManager::getAllAssetsOfType(UVK::ASSET_TYPE_VIDEO))
        {
            if (ImGui::MenuItem((a.name + "##" + a.path).c_str()))
            {
                name = a.name;
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}
#endif