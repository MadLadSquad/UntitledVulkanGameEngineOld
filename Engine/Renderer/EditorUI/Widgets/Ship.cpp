// Ship.cpp
// Last update 1/8/2021 by Madman10K
#include "Ship.hpp"
#ifndef PRODUCTION
#include "imgui.h"
#include <future>

void Shipping::display(bool& bShow)
{
    if (!ImGui::IsPopupOpen("Shipping"))
        ImGui::OpenPopup("Shipping");

    if (ImGui::BeginPopupModal("Shipping", &bShow))
    {
        ImGui::TextWrapped("Compile your program for testing or production!");
        ImGui::Separator();
        ImGui::TextWrapped("Warning: This feature is only available on Unix systems");
        ImGui::TextWrapped("A guide for Windows is available in the Wiki. Link is in the 'Help' window under the 'More' tab");
        ImGui::Separator();

        static int jobs = 1;
        static bool testing = false;
        ImGui::TextWrapped("Compile jobs");
        ImGui::SameLine();
        ImGui::InputInt("##Compile jobs", &jobs);

        ImGui::TextWrapped("Testing?");
        ImGui::SameLine();
        ImGui::Checkbox("##Testing?", &testing);

        ImGui::TextWrapped("The testing option is when you want a build for internal testing without archiving the assets(not implemented yet)");
        ImGui::Separator();
        ImGui::TextWrapped("If you click 'Compile' your editor will freeze, output from the compiling is in the terminal, after it is done it will return to normal.");
        ImGui::Separator();
        ImGui::TextWrapped("After the process is done, you can run your app, located in the 'Exported' folder");
        if (ImGui::Button("Close##compile"))
        {
            bShow = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Compile##compile"))
        {
#ifndef _WIN32
            int8_t lnt;
            auto a = std::async(std::launch::async, [&]() {
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build/ && ./UVKBuildTool --build " + std::to_string(jobs)).c_str());
            });

            a.get();

            if (lnt)
            {

            }
            bShow = false;
#else
            bShow = false;
#endif
        }
        ImGui::EndPopup();
    }
}
#endif