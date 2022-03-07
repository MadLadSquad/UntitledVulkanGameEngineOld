// ProjectSettings.cpp
// Last update 18/2/2022 by Madman10K
#pragma once

namespace UVK::ProjectSettingsWidget
{
    void displayProjectSettings(bool& bReturn, std::string& name, std::string& ver, std::string& enginever, std::string& startupLevel, bool& bOpen, const YAML::Node& node);
}