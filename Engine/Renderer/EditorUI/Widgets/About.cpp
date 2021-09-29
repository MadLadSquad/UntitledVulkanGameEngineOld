// About.cpp
// Last update 12/8/2021 by Madman10K
#include <GL/glew.h>
#include "About.hpp"
#ifndef PRODUCTION
#include "AssetSlot.hpp"

void About::display(std::string& engineVersion, std::string& projectName, std::string& projectVersion, UVK::Texture& logo, bool& bShow)
{
    if (!ImGui::IsPopupOpen("About us"))
        ImGui::OpenPopup("About us");
    if (ImGui::BeginPopupModal("About us", &bShow))
    {
        ImGui::TextWrapped("Untitled Vulkan Game Engine, version %s", engineVersion.c_str());
        ImGui::TextWrapped("Currently editing %s, version %s", projectName.c_str(), projectVersion.c_str());
        ImGui::Separator();
        ImGui::TextWrapped("The Untitled Vulkan Game Engine is brought to you by MadLad Squad");
        ImGui::TextWrapped("Project created and maintained by Stanislav Vasilev (Madman10K)");
        ImGui::Image((void*)(intptr_t)logo.getImage(), ImVec2((float)logo.getWidth() - 100, (float)logo.getHeight() - 100));

        /*static bool first = true;
        static UVK::Texture remove;
        if (first)
        {
            remove = UVK::Texture("../Content/Engine/close.png");
            remove.loadImgui();
            first = false;
        }


        AssetSlot::displayTexture(0, logo, remove, &remove);
        */
        if (ImGui::Button("Close##AboutUS"))
        {
            bShow = false;
        }
        ImGui::EndPopup();
    }
}
#endif