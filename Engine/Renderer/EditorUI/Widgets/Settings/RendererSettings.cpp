#include "RendererSettings.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <Core/Global.hpp>
#include <Renderer/EditorUI/Editor.hpp>

void UVK::RendererSettingsWidget::display(bool& bReturn, bool& bOpen, Editor& editor) noexcept
{
    ImGui::TextWrapped("DISCLAIMER: The editor needs to be reloaded for changes to appear!");

    static bool bVulkan = false;
    static bool first = false;
    if (!first)
    {
        bVulkan = UVK::global.bUsesVulkan;
        first = true;
    }

    ImGui::TextWrapped("Vulkan");
    ImGui::SameLine();
    ImGui::Checkbox("##Vulkan", &bVulkan);

    ImGui::TextWrapped("Theme Location");
    ImGui::SameLine();
    if (ImGui::InputText("##Theme Location", &UVK::SettingsManager::getRendererSettings().themeLoc) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("V-Sync");
    ImGui::SameLine();
    ImGui::Checkbox("##V-Sync", &UVK::Renderer::getVSync());

    ImGui::TextWrapped("Immediate Frame Display");
    ImGui::SameLine();
    ImGui::Checkbox("##V-Sync immediate", &UVK::Renderer::getImmediateRender());

    ImGui::TextWrapped("Filesystem Element Padding");
    ImGui::SameLine();
    if (ImGui::InputScalar("##FilesystemElementPadding", ImGuiDataType_Float, &editor.settings.fsdata.padding) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Filesystem Element Image Size");
    ImGui::SameLine();
    if (ImGui::InputScalar("##FilesystemElementImageSize", ImGuiDataType_Float, &editor.settings.fsdata.imageSize) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Filesystem Use Previews");
    ImGui::SameLine();
    ImGui::Checkbox("##FilesystemPreviews", &editor.settings.fsdata.bUsePreviews);

    ImGui::TextWrapped("Filesystem Max Elements With Previews");
    ImGui::SameLine();
    if (ImGui::InputScalar("##FilesystemMaxElementsWithPreviews", ImGuiDataType_U32, &editor.settings.fsdata.maxFileNum) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Max MSAA samples");
    ImGui::SameLine();
    if (ImGui::InputScalar("##MSAAMAXSAMPLES", ImGuiDataType_U32, &UVK::Renderer::msaaSampleCount()) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Sample rate shading");
    ImGui::SameLine();
    ImGui::Checkbox("##SampleRateShadingCheck", &Renderer::sampleRateShading());

    ImGui::TextWrapped("Sample rate shading mult");
    ImGui::SameLine();
    if (ImGui::InputScalar("##MSAAMAXSAMPLES", ImGuiDataType_Float, &UVK::Renderer::sampleRateShadingMult()) || ImGui::IsItemActive())
        bReturn = true;

    if (ImGui::Button("Close"))
    {
        bOpen = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        bool temp = UVK::global.bUsesVulkan;
        UVK::global.bUsesVulkan = bVulkan;
        UVK::SettingsManager::saveRendererSettings();
        UVK::global.bUsesVulkan = temp;
    }
    ImGui::EndPopup();
}