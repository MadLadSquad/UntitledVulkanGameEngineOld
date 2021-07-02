// GLPipeline.cpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include <Events/Events.hpp>
#include <Renderer/EditorUI/Classes/EditorLevel.hpp>
#include <Renderer/OpenGL/Pipeline/GLEntityManager.hpp>
#include "GLPipeline.hpp"


void UVK::GLPipeline::begin(bool bHasEditor, Level* lvl)
{
    bEditor = bHasEditor;

    global.window.createWindow();

    if (bEditor)
    {
#ifndef PRODUCTION
        auto* lv = new UVK::EditorLevel;
        global.level = lv;

        Actor a("Editor Pawn", 330, "EditorPawn");
        global.level->gameMode->pawn->beginPlay();
    #ifdef DEVELOPMENT
        tx = Texture("../Content/Engine/brick.jpg");
        tx.load();
    #endif
        ed.setTheme(colTheme);
        ed.initEditor();
#endif
    }
    else
    {
        global.ui.init();
        global.level->beginPlay();
    }
    enableFeatures();
}

void UVK::GLPipeline::tick()
{
    glfwPollEvents();

    auto now = (float)glfwGetTime();
    deltaTime = now - lastTime;
    lastTime = now;

    if (bEditor)
    {
        fb.useFramebuffer();
        glEnable(GL_DEPTH_TEST);

        glClearColor(global.colour.x, global.colour.y, global.colour.z, global.colour.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        UVK::Editor::beginFrame();
        global.level->gameMode->pawn->tick(deltaTime);
#ifdef DEVELOPMENT
        tx.useTexture();
#endif
    }
    else
    {
        glClearColor(global.colour.x, global.colour.y, global.colour.z, global.colour.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        UVK::UI::beginFrame();
    }

    UVK::GLEntityManager::tick(&global.level->gameMode->pawn->camera);

    glUseProgram(0);

    if (bEditor)
    {
#ifndef PRODUCTION
        UVK::GLFrameBuffer::unbindFramebuffer();
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ed.runEditor(global.colour, fb, global.level->gameMode->pawn->camera, global.level);
#endif
    }
    else
    {
        global.level->tick(deltaTime);
        global.events.callTick(deltaTime);
        global.ui.update();

        global.finalizeOpening();
    }

    glfwSwapBuffers(global.window.getWindow());
}

void UVK::GLPipeline::end()
{
    if (bEditor)
    {
#ifndef PRODUCTION
        ed.destroyContext();
        global.level->gameMode->pawn->endPlay();
#endif
    }
    else
    {
        global.level->endPlay();
        global.events.callEnd();
        UVK::UI::clean();
    }

    UVK::GLEntityManager::clean();
}

void UVK::GLPipeline::enableFeatures()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
}

UVK::GLPipeline::GLPipeline(bool bHasEditor, UVK::Level *lvl)
{
    begin(bHasEditor, lvl);
}
