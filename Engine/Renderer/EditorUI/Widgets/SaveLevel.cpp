// SaveLevel.cpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include "SaveLevel.hpp"
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"

#ifndef PRODUCTION
void SaveLevel::display(bool &bOpen, std::string &location, std::string &name, UVK::FVector4& colour, UVK::Texture& insert, const std::string& cpFileLoc)
{
    ImGui::Begin("Save level", &bOpen);

    ImGui::InputText("location##inputlocationsave", &location);
    ImGui::SameLine();
    if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.0f, 10.0f)))
    {
        location = cpFileLoc;
    }

    // TODO: Fix problem with insertion here
    ImGui::InputText("name##inputnamesave", &name);
    ImGui::SameLine();
    if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.0f, 10.0f)))
    {
        name = cpFileLoc;
    }

    if (ImGui::Button("Cancel##cancelbuttononsave"))
    {
        bOpen = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Submit##submitbuttononsave"))
    {
        UVK::Level::save(location.c_str());
        bOpen = false;
    }

    ImGui::End();
}
#endif