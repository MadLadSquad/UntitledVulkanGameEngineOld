// TopToolbar.cpp
// Last update 18/2/2022 by Madman10K
#include "TopToolbar.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <Renderer/EditorUI/Modules/EditorModule.hpp>
#include <imguiex/uexec/uexec.h>

bool TopToolbar::display(UVK::Texture& play, const std::string& projectName, const UVK::EditorModuleManager& modules, bool& bShow, UVK::Texture& restart, UVK::Texture& stop)
{
    static uexec::ScriptRunner runner;
    static bool bShowPlay = true;
    bool bReturn = false;

    ImGui::Begin("Toolbar", &bShow);

    if (bShowPlay)
    {
        if (ImGui::ImageButton((void*)(intptr_t)play.getImage(), ImVec2(50.0f, 50.0f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0) && runner.startable())
            startProcess(projectName, runner, bShowPlay);
    }
    else
    {
        if (ImGui::ImageButton((void*)(intptr_t)restart.getImage(), ImVec2(50.0f, 50.0f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0))
        {
            runner.terminate();
            runner.destroy();
            runner.destroyForReuse();

            startProcess(projectName, runner, bShowPlay);
        }
        ImGui::SameLine();
        if (ImGui::ImageButton((void*)(intptr_t)stop.getImage(), ImVec2(50.0f, 50.0f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0))
        {
            runner.terminate();
            runner.destroy();
            runner.destroyForReuse();
            bShowPlay = true;
        }
    }

    if (runner.finished())
    {
        runner.destroy();
        runner.destroyForReuse();
        bShowPlay = true;
    }

    modules.renderTopBar(bReturn);

    ImGui::End();
    return bReturn;
}

void TopToolbar::startProcess(const std::string& projectName, uexec::ScriptRunner& runner, bool& bShowPlay)
{
#ifdef _WIN32
    auto str = "./" + projectName + ".exe";
#else
    auto str = "./" + projectName;
#endif
    char* const args[] = { str.data(), nullptr };
    runner.init(args, 64);
    runner.updateBufferSize();
    runner.update(true);
    bShowPlay = false;
}
#endif