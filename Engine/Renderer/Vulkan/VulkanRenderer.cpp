// VulkanRenderer.cpp
// Last update 21/12/2021 by Madman10K
#ifndef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include "VulkanRenderer.hpp"
#include "Renderer/EditorUI/Classes/EditorLevel.hpp"
#include "VKEntityManager.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <glfw3.h>

void UVK::VulkanRenderer::run()
{
    Timer setup;
    setup.startRecording();
    global.window.createWindow();

    if (global.getEditor())
    {
#ifndef PRODUCTION
        delete global.currentLevel;
        auto* lv = new UVK::EditorLevel;
        global.currentLevel = lv;
        global.currentLevel->beginPlay();
        colTheme = global.rendererSettings.themeLoc.c_str();
        ed.setTheme(colTheme);
        ed.initEditor();
        global.instance->onEventInitEditorModules(); // Always call after the editor is instantiated
#endif
    }
    else
    {
#ifndef PRODUCTION
        if (global.currentLevel->gameMode == nullptr)
        {
            global.currentLevel->gameMode = GameMode::makeGameMode<EditorGameMode>();
        }

        if (UVK::Level::getPawn(UVK::global.currentLevel) == nullptr)
        {
            global.currentLevel->gameMode->playerController->pawn = Pawn::makePawn<EditorPawn>();
        }
#endif
        global.ui.init();
        global.instance->beginPlay();
        global.currentLevel->beginPlay();
    }

    float deltaTime;
    float lastTime = 0;
    setup.stopRecording();
    logger.consoleLog("Starting the Vulkan renderer took ", UVK_LOG_TYPE_NOTE, setup.getDuration(), "ms");

    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        glfwPollEvents();
        auto now = (float)glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

#ifndef PRODUCTION
        if (global.getEditor())
        {
            //fb.useFramebuffer();
            //glEnable(GL_DEPTH_TEST);

            //glClearColor(global.colour.x, global.colour.y, global.colour.z, global.colour.w);
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            UVK::Editor::beginFrame();
            global.currentLevel->tick(deltaTime);
        }
        else
        {
            //glClearColor(global.colour.x, global.colour.y, global.colour.z, global.colour.w);
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            UVK::UIInternal::beginFrame();

            global.currentLevel->tick(deltaTime);
            Events::callTick(deltaTime);
            global.ui.update();
        }
#else
    //glClearColor(global.colour.x, global.colour.y, global.colour.z, global.colour.w);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    UVK::UIInternal::beginFrame();

    global.currentLevel->tick(deltaTime);
    Events::callTick(deltaTime);
    global.ui.update();
#endif

        UVK::VKEntityManager::tick(&UVK::Level::getPawn(UVK::global.currentLevel)->camera);

        //glUseProgram(0);

#ifndef PRODUCTION
        if (global.getEditor())
        {

            //UVK::GLFrameBuffer::unbindFramebuffer();
            //glDisable(GL_DEPTH_TEST);
            //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            //glClear(GL_COLOR_BUFFER_BIT);

            //ed.runEditor(global.colour, fb, UVK::Level::getPawn(UVK::global.currentLevel)->camera, global.currentLevel, deltaTime);
        }
#endif
        global.finalizeOpening();
    }
    if (global.getEditor())
    {
#ifndef PRODUCTION
        ed.destroyContext();
        UVK::Level::getPawn(UVK::global.currentLevel)->endPlay();
#endif
    }
    else
    {
        global.currentLevel->endPlay();
        Events::callEnd();
        global.instance->endPlay();
        UVK::UIInternal::clean();
        global.window.destroyWindow();
    }

    UVK::VKEntityManager::clean();
}
#endif