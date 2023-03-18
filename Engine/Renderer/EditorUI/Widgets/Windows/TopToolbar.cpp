#include "TopToolbar.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <Renderer/EditorUI/Modules/EditorModule.hpp>
#include <imguiex/uexec/uexec.hpp>

bool TopToolbar::display(UVK::Texture& play, const UVK::FString& projectName, const UVK::EditorModuleManager& modules, bool& bShow, UVK::Texture& restart, UVK::Texture& stop) noexcept
{
    static uexec::ScriptRunner runner;
    static bool bShowPlay = true;
    bool bReturn = false;

    ImGui::Begin("Toolbar", &bShow);

    // If true will show only the play button otherwise will show the close and restart buttons
    if (bShowPlay)
    {
        if (ImGui::ImageButton("##playbutton", (void*)(intptr_t)play.getImage(), ImVec2(50.0f, 50.0f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImVec4(0, 0, 0, 0)) && runner.startable())
            startProcess(projectName, runner, bShowPlay);
    }
    else
    {
        if (ImGui::ImageButton("##restartbutton", (void*)(intptr_t)restart.getImage(), ImVec2(50.0f, 50.0f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImVec4(0, 0, 0, 0)))
        {
            runner.terminate();
            runner.destroy();
            runner.destroyForReuse();

            startProcess(projectName, runner, bShowPlay);
        }
        ImGui::SameLine();
        if (ImGui::ImageButton("##stopbutton", (void*)(intptr_t)stop.getImage(), ImVec2(50.0f, 50.0f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImVec4(0, 0, 0, 0)))
        {
            runner.terminate();
            runner.destroy();
            runner.destroyForReuse();
            bShowPlay = true;
        }
    }

    // Cleanup after running
    if (runner.finished())
    {
        runner.destroy();
        runner.destroyForReuse();
        bShowPlay = true;
    }

    // Render the editor modules
    modules.renderTopBar(bReturn);

    ImGui::End();
    return bReturn;
}

void TopToolbar::startProcess(const UVK::FString& projectName, uexec::ScriptRunner& runner, bool& bShowPlay) noexcept
{
#ifdef _WIN32
    auto str = "./" + projectName + ".exe";
#else
    auto str = "./" + projectName;
#endif
    char* const args[] = { str.data(), nullptr };
    runner.init(args, 64);
    runner.update();
    bShowPlay = false;
}
#endif
