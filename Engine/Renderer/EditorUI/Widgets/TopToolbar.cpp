// TopToolbar.cpp
// Last update 17/10/2021 by Madman10K
#include "TopToolbar.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <Renderer/EditorUI/Modules/EditorModule.hpp>
#include <imguiex/uexec/uexec.h>

bool TopToolbar::display(UVK::Texture& play, std::string& projectName, const UVK::EditorModuleManager& modules, bool& bShow)
{
    bool bReturn = false;
    int8_t lnt = 0;

    ImGui::Begin("Toolbar", &bShow);

    if (ImGui::ImageButton((void*)(intptr_t)play.getImage(), ImVec2((float)50, (float)50), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0))
    {
#ifdef _WIN32
        lnt = system(static_cast<std::string>(projectName + ".exe").c_str());
#else
        static uexec::ScriptRunner runner;
        char* const args[] = { projectName.data(), nullptr };
        runner.init(args, 1);
        runner.updateBufferSize();
        runner.update(true);

        lnt = system(static_cast<std::string>("./" + projectName).c_str());
#endif
    }

    modules.renderTopBar(bReturn);

    if (lnt)
    {

    }

    ImGui::End();
    return bReturn;
}
#endif