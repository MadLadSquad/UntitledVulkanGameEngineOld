// Ship.cpp
// Last update 18/2/2022 by Madman10K
#include "Ship.hpp"
#ifndef PRODUCTION
#include "imgui.h"
#include <UVKBuildTool/src/ReleaseBuild.hpp>
#include <imguiex/uexec/uexec.h>

bool Shipping::display(bool& bShow, const std::string& prjname)
{
    static uexec::ScriptRunner runner;
    static bool bShowPlay = true;

    if (!ImGui::IsPopupOpen("Shipping"))
        ImGui::OpenPopup("Shipping");
    if (ImGui::BeginPopupModal("Shipping"))
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

        if (bShowPlay)
        {
            if (ImGui::Button("Close##compile"))
            {
                bShow = false;
            }

            ImGui::SameLine();

            if (ImGui::Button("Compile##compile"))
            {
                // TODO: Add archiving after we are out of Pre-Alpha
                std::ofstream out("../Generated/BuildDef.hpp");
                out << "#define PRODUCTION" << std::endl;
                out.close();

#ifdef _WIN32
                std::string str = "bash ../export.sh " + prjname;
                char* const args[] = { str.data(), nullptr };
#else
                std::string str = "cd ../ && ./export.sh " + prjname;
                char* const args[] = { (char*)"bash", (char*)"-c", str.data(), nullptr };
#endif

                runner.init(args, 64);
                runner.updateBufferSize();
                runner.update(true);
                bShowPlay = false;
            }
        }
        else
        {
            if (ImGui::Button("Stop##compile"))
            {
                runner.terminate();
                runner.destroy();
                runner.destroyForReuse();

                bShowPlay = false;
            }
        }

        if (runner.finished())
        {
            runner.destroy();
            runner.destroyForReuse();
            bShowPlay = true;
            std::ofstream out("../Generated/BuildDef.hpp");
            out << "// Generated file, DO NOT TOUCH!" << std::endl;
            out << "#undef PRODUCTION" << std::endl;
            out.close();
        }

        ImGui::EndPopup();
    }
    return false;
}
#endif