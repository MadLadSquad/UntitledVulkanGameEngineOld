// SaveLevel.cpp
// Last update 5/5/2021 by Madman10K
#include "SaveLevel.hpp"
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"

void SaveLevel::display(bool &bOpen, std::string &location, std::string &name)
{
    ImGui::Begin("Save level");

    ImGui::InputText("location##inputlocationsave", &location);
    ImGui::InputText("name##inputnamesave", &name);

    if (ImGui::Button("Submit##submitbuttononsave"))
    {

        UVK::Level::save(location.c_str(), name.c_str());
        bOpen = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel##cancelbuttononsave"))
    {
        bOpen = false;
    }

    ImGui::End();
}