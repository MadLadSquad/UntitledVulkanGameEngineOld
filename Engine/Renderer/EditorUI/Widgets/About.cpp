// About.cpp
// Last update 15/6/2021 by Madman10K
#include "About.hpp"
#ifndef PRODUCTION
void About::display(std::string& engineVersion, std::string& projectName, std::string& projectVersion, UVK::Texture& logo, bool& bShow)
{
    ImGui::Begin("About us", &bShow);

    ImGui::Text("Untitled Vulkan Game Engine, version %s", engineVersion.c_str());
    ImGui::Text("Currently editing %s, version %s", projectName.c_str(), projectVersion.c_str());
    ImGui::Text(" ");
    ImGui::Text("The Untitled Vulkan Game Engine is brought to you by MadLad Squad");
    ImGui::Text("Project created and maintained by Stanislav Vasilev (Madman10K)");
    ImGui::Image((void*)(intptr_t)logo.getImage(), ImVec2((float)logo.getWidth() - 100, (float)logo.getHeight() - 100));

    if (ImGui::Button("Close##AboutUS"))
    {
        bShow = false;
    }
    ImGui::End();
}
#endif