// Ship.cpp
// Last update 16/6/2021 by Madman10K
#include "Ship.hpp"
#include "imgui.h"
#include <future>

void Shipping::display(bool& bShow)
{
    ImGui::Begin("Shipping", &bShow);

    ImGui::Text("Compile your program for testing or production!");
    ImGui::Text(" ");
    ImGui::Text("Warning: This feature is only available on Unix systems");
    ImGui::Text("A guide for Windows is available in the Wiki. Link is in the 'Help' window under the 'More' tab");

    static int jobs = 1;
    static bool testing = false;
    ImGui::InputInt("Compile jobs", &jobs);
    ImGui::Checkbox("Testing?", &testing);

    ImGui::Text("The testing option is when you want a build for internal testing without archiving the assets(not implemented yet)");

    ImGui::Text(" ");

    ImGui::Text("If you click 'Compile' your editor will freeze, output from the compiling is in the terminal, after it is done it will return to normal.");
    ImGui::Text("Also after the process is done, you can run your app, located in the 'Exported' folder");
    if (ImGui::Button("Close##compile"))
    {
        bShow = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Compile##compile"))
    {
#ifndef _WIN32
        int lnt;
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
    ImGui::End();
}