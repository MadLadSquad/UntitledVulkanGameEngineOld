#include "Structs.hpp"
#include <Renderer/EditorUI/Editor.hpp>

void UVK::EditorSettings::writeToFile(Editor& editor) const
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "max-saved-transactions" << YAML::Value << maxSavedTransactions;
    out << YAML::Key << "filesystem-file-padding" << YAML::Value << editor.settings.fsdata.padding;
    out << YAML::Key << "filesystem-file-thumbnail-size" << YAML::Value << editor.settings.fsdata.imageSize;
    out << YAML::Key << "filesystem-using-previews" << YAML::Value << editor.settings.fsdata.bUsePreviews;
    out << YAML::Key << "filesystem-max-preview-files" << YAML::Value << editor.settings.fsdata.maxFileNum;
    out << YAML::Key << "editor-layout-location" << YAML::Value << editorLayoutLocation << ".ini";

    out << YAML::EndMap;

    std::ofstream fileout("../Config/Settings/Editor.yaml");
    fileout << out.c_str();
}