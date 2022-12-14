#include "Ship.hpp"
#ifndef PRODUCTION
#include "imgui.h"
#include <UVKBuildTool/src/UntitledVulkanGameEngine/ReleaseBuild.hpp>
#include <imguiex/uexec/uexec.hpp>

bool Shipping::display(bool& bShow, const UVK::FString& prjname) noexcept
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

        // If this is true we can begin compilation, otherwise we're already compiling and can only stop it
        if (bShowPlay)
        {
            if (ImGui::Button("Close##compile"))
                bShow = false;

            ImGui::SameLine();

            if (ImGui::Button("Compile##compile"))
            {
                // TODO: Add archiving after we are out of Pre-Alpha
                std::ofstream out((UVK::FString(UVK_CONFIG_PRJ_PATH) + "Generated/BuildDef.hpp").c_str());
                out << "#define PRODUCTION" << std::endl;
                out.close();

#ifdef _WIN32
                UVK::FString str = "bash ../export.sh " + prjname;
                char* const args[] = { str.data(), nullptr };
#else
                UVK::FString str = "cd ../ && ./export.sh " + prjname;
                char* const args[] = { (char*)"bash", (char*)"-c", str.data(), nullptr };
#endif

                runner.init(args, 64);
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

        // Post action steps when the runner finishes its compilation work
        if (runner.finished())
        {
            runner.destroy();
            runner.destroyForReuse();
            bShowPlay = true;
            std::ofstream out((UVK::FString(UVK_CONFIG_PRJ_PATH) + "Generated/BuildDef.hpp").c_str());
            out << "// Generated file, DO NOT TOUCH!" << std::endl;
            out << "#undef PRODUCTION" << std::endl;
            out.close();
        }

        ImGui::EndPopup();
    }
    return false;
}
#endif
