// TopToolbar.cpp
// Last update 17/10/2021 by Madman10K
#include "TopToolbar.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <Renderer/EditorUI/Modules/EditorModule.hpp>
#include <imguiex/uexec/uexec.h>
#ifdef _WIN32
    #include <windows.h>
	#include <iostream>
#else
    #include <unistd.h>
    #include <sys/wait.h>
#endif

bool TopToolbar::display(UVK::Texture& play, const std::string& projectName, const UVK::EditorModuleManager& modules, bool& bShow)
{
    static uexec::ScriptRunner runner;
    bool bReturn = false;
    int8_t lnt = 0;

    ImGui::Begin("Toolbar", &bShow);

    if (ImGui::ImageButton((void*)(intptr_t)play.getImage(), ImVec2((float)50, (float)50), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0) && runner.startable())
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
    }

    if (runner.finished())
    {
        runner.destroy();
        runner.destroyForReuse();
    }

    modules.renderTopBar(bReturn);

    if (lnt)
    {

    }

    ImGui::End();
    return bReturn;
}
#endif