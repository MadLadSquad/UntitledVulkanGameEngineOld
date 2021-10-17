// Ship.cpp
// Last update 17/10/2021 by Madman10K
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
        ImGui::ShowDemoWindow();
        ImGui::Separator();

        static int jobs = 1;
        static bool testing = false;
        ImGui::TextWrapped("Compile jobs");
        ImGui::SameLine();
        if (ImGui::InputScalar("##Compile jobs", ImGuiDataType_U32, &jobs) || ImGui::IsItemFocused())
            bReturn = true;

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
    return bReturn;
}
#endif