// Ship.cpp
// Last update 18/2/2022 by Madman10K
#include "Ship.hpp"
#ifndef PRODUCTION
#include "imgui.h"
#include <future>

bool Shipping::display(bool& bShow)
{
    bool bReturn = false;
    if (!ImGui::IsPopupOpen("Shipping"))
        ImGui::OpenPopup("Shipping");

    if (ImGui::BeginPopupModal("Shipping", &bShow))
    {
        ImGui::TextWrapped("Compile your program for testing or production!");
        ImGui::SameLine();
        ImGui::Separator();

        static bool testing = false;

        ImGui::TextWrapped("Testing?");
        ImGui::SameLine();
        ImGui::Checkbox("##Testing?", &testing);

        ImGui::TextWrapped("If you click 'Compile' your editor will freeze, output from the compilation is in the terminal, after it is done it will return to normal.");
        ImGui::Separator();
        ImGui::TextWrapped("After the process is done, you can run your app, located in the 'Exported' folder");
        if (ImGui::Button("Close##compile"))
        {
            bShow = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Compile##compile"))
        {
            auto a = std::async(std::launch::async, [&]() {
                int8_t lnt;
#ifndef _WIN32
                lnt = system("cd ../UVKBuildTool/build/ && ./UVKBuildTool --build");
#else
                lnt = system("cd ../UVKBuildTool/build/ && UVKBuildTool.exe --build");
#endif
                return lnt;
            });
            a.get();

            bShow = false;
        }
        ImGui::EndPopup();
    }
    return bReturn;
}
#endif