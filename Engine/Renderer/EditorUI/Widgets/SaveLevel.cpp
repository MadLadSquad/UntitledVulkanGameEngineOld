// SaveLevel.cpp
// Last update 6/7/2021 by Madman10K
#include <GL/glew.h>
#include "SaveLevel.hpp"
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"

#ifndef PRODUCTION
void SaveLevel::display(bool &bOpen, std::string &location, std::string &name, UVK::FVector4& colour, UVK::Texture& insert, const std::string& cpFileLoc)
{
    ImGui::Begin("Save level", &bOpen);

    ImGui::InputTextWithHint("location##inputlocationsave", "Location starting from the Content directory", &location);
    ImGui::SameLine();
    if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.0f, 10.0f)))
    {
        location = cpFileLoc;
    }

    ImGui::InputTextWithHint("name##inputnamesave", "Internal name of the level (NOT THE FILENAME)", &name);

    if (ImGui::Button("Cancel##cancelbuttononsave"))
    {
        bOpen = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Submit##submitbuttononsave"))
    {
        UVK::Level::save(static_cast<std::string>("../Content/" + location).c_str());
        bOpen = false;
    }

    ImGui::End();
}
#endif