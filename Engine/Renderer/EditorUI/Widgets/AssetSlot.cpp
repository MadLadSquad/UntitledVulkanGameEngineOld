// AssetSlot.cpp
// Last update 8/11/2021 by Madman10K
#include "AssetSlot.hpp"

#ifndef PRODUCTION
#include <Renderer/EditorUI/Editor.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>

void AssetSlot::assetSlotBegin(UVK::Texture& thumbnail, const int32_t& id, const std::function<void(void)>& function)
{
    ImGui::BeginGroup();
    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, 66.0f);
    ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 0.0f, 0.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.0f, 0.0f });
    ImGui::ImageButton((void*)(intptr_t)thumbnail.getImage(), { 50.0f, 50.0f });
    function();
    ImGui::PopStyleColor(3);
    ImGui::NextColumn();
    ImGui::PushID(id);
}

void AssetSlot::assetSlotEnd()
{
    ImGui::PopID();
    ImGui::NextColumn();
    ImGui::Columns(1);
    ImGui::EndGroup();
}

void AssetSlot::displayTexture(int32_t id, UVK::Texture* asset, std::string& name)
{
    UVK::EditorPointer editorPointer;

    assetSlotBegin(editorPointer.fsicons()[FS_ICON_IMAGE], id, [&](){
        if (ImGui::BeginDragDropTarget())
        {
            if (const auto* payload = ImGui::AcceptDragDropPayload("ENGINE_FS_WIDGET_ALL"))
            {
                std::string str = (const char*)payload->Data;
                str.erase(payload->DataSize);
                static constexpr const char* imageExtensions[] = { ".jpeg", ".jpg", ".tiff", ".gif", ".bmp", ".png", ".tga", ".psd", ".pic" };
                for (auto imageExtension : imageExtensions)
                    if (str.ends_with(imageExtension))
                        name = str;
            }
            ImGui::EndDragDropTarget();
        }
    });

    ImGui::TextWrapped("%s", name.c_str());

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayAudio(int32_t id, UVK::Texture* asset, std::string& name)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_AUDIO], id, [&]()
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const auto* payload = ImGui::AcceptDragDropPayload("ENGINE_FS_WIDGET_ALL"))
            {
                std::string str = (const char*)payload->Data;
                str.erase(payload->DataSize);
                static constexpr const char* audioExtensions[] = { ".wav", ".flac", ".m4a", ".ogg", ".mp3" };
                for (auto imageExtension : audioExtensions)
                    if (str.ends_with(imageExtension))
                        name = str;
            }
            ImGui::EndDragDropTarget();
        }
    });
    ImGui::TextWrapped("%s", name.c_str());

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayFont(int32_t id, UVK::Texture* asset, std::string& name)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_FONT], id, [&]()
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const auto* payload = ImGui::AcceptDragDropPayload("ENGINE_FS_WIDGET_ALL"))
            {
                std::string str = (const char*)payload->Data;
                str.erase(payload->DataSize);
                if (str.ends_with(".ttf"))
                    name = str;
            }
            ImGui::EndDragDropTarget();
        }
    });

    ImGui::TextWrapped("%s", name.c_str());

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayModel(int32_t id, UVK::Texture* asset, std::string& name)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_MODEL], id, [&]()
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const auto* payload = ImGui::AcceptDragDropPayload("ENGINE_FS_WIDGET_ALL"))
            {
                std::string str = (const char*)payload->Data;
                str.erase(payload->DataSize);
                static constexpr const char* objExtensions[] = { ".obj", ".fbx", ".glb", ".gltf" };
                for (auto imageExtension : objExtensions)
                    if (str.ends_with(imageExtension))
                        name = str;
            }
            ImGui::EndDragDropTarget();
        }
    });

    ImGui::TextWrapped("%s", name.c_str());

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayShaders(int32_t id, UVK::Texture* asset, std::string& name)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_CODE], id, [&]()
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const auto* payload = ImGui::AcceptDragDropPayload("ENGINE_FS_WIDGET_ALL"))
            {
                std::string str = (const char*)payload->Data;
                str.erase(payload->DataSize);
                static constexpr const char* shaderExtensions[] = { ".glsl", ".vshader.glsl", ".fshader.glsl", ".vshader", ".fshader" };
                for (auto imageExtension : shaderExtensions)
                    if (str.ends_with(imageExtension))
                        name = str;
            }
            ImGui::EndDragDropTarget();
        }
    });

    ImGui::TextWrapped("%s", name.c_str());

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}

void AssetSlot::displayVideo(int32_t id, UVK::Texture* asset, std::string& name)
{
    UVK::EditorPointer editorPointer;
    assetSlotBegin(editorPointer.fsicons()[FS_ICON_VIDEO], id, [&]()
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const auto* payload = ImGui::AcceptDragDropPayload("ENGINE_FS_WIDGET_ALL"))
            {
                std::string str = (const char*)payload->Data;
                str.erase(payload->DataSize);
                static constexpr const char* videoExtensions[] = { ".mov", ".m4v", ".mp4", ".mpeg", ".mkv", ".mpg", ".wmv", ".webm" };
                for (auto imageExtension : videoExtensions)
                    if (str.ends_with(imageExtension))
                        name = str;
            }
            ImGui::EndDragDropTarget();
        }
    });

    ImGui::TextWrapped("%s", name.c_str());

    if (ImGui::ImageButton((void*)(intptr_t)editorPointer.fsicons()[FS_ICON_CLOSE].getImage(), { 16.0f, 16.0f }))
    {
        asset = nullptr;
        name = "None";
    }
    assetSlotEnd();
}
#endif