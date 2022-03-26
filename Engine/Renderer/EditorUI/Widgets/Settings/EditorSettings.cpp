#include "EditorSettings.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <Renderer/EditorUI/Editor.hpp>

void UVK::EditorSettingsWidget::displayEditorSettingsWidget(bool& bReturn, bool& bOpen, Editor& editor) noexcept
{
    ImGui::TextWrapped("Max stored transactions");
    ImGui::SameLine();
    if (ImGui::InputScalar("##max-stored-transactions", ImGuiDataType_U32, &editor.settings.maxSavedTransactions) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Filesystem file padding");
    ImGui::SameLine();
    if (ImGui::InputScalar("##filesystem-file-padding", ImGuiDataType_Float, &editor.settings.fsdata.padding) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Filesystem thumbnail size");
    ImGui::SameLine();
    if (ImGui::InputScalar("##Filesystem thumbnail size", ImGuiDataType_Float, &editor.settings.fsdata.imageSize) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Using previews in the filesystem?");
    ImGui::SameLine();
    ImGui::Checkbox("##using-previews-filesystem", &editor.settings.fsdata.bUsePreviews);

    ImGui::TextWrapped("Filesystem max previews");
    ImGui::SameLine();
    if (ImGui::InputScalar("##max-stored-transactions", ImGuiDataType_U32, &editor.settings.fsdata.maxFileNum) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Editor layout file location");
    ImGui::SameLine();
    if (ImGui::InputText("##editor-layout-file-location", &editor.settings.editorLayoutLocation) || ImGui::IsItemActive())
        bReturn = true;
    ImGui::SameLine();
    ImGui::TextWrapped(".ini");

    if (ImGui::Button("Cancel"))
        bOpen = false;
    ImGui::SameLine();
    if (ImGui::Button("Save"))
        editor.settings.writeToFile(editor);
}