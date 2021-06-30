// SaveLevel.cpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include "SaveLevel.hpp"
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"

#ifndef PRODUCTION
void SaveLevel::display(bool &bOpen, std::string &location, std::string &name, UVK::FVector4& colour)
{
    ImGui::Begin("Save level");

    ImGui::InputText("location##inputlocationsave", &location);
    ImGui::InputText("name##inputnamesave", &name);

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