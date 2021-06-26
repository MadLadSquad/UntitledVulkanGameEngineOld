// GLPipeline.cpp
// Last update 26/6/2021 by Madman10K
#include <GL/glew.h>
#include <Events/Events.hpp>
#include <Renderer/EditorUI/Classes/EditorLevel.hpp>
#include <Renderer/OpenGL/Pipeline/GLEntityManager.hpp>
#include <Renderer/Window/Window.hpp>
#include <Renderer/RendererResources.hpp>
#include <Core/Registry.hpp>
#include "GLPipeline.hpp"


void UVK::GLPipeline::begin(bool bHasEditor, Level* lvl)
{
    level = lvl;
    bEditor = bHasEditor;

    currentWindow.createWindow();

    if (!bEditor)
    {
        events.callBegin();
    }
    else
    {
#ifndef PRODUCTION
        auto* lv = new UVK::EditorLevel;
        level = lv;

        auto a = pool.create();
        auto& cmp = pool.emplace<UVK::CoreComponent>(a);
        cmp.name = "Editor Pawn";
        cmp.id = 330;
        cmp.devName = "EditorPawn";
        level->gameMode->pawn->beginPlay();
#ifdef DEVELOPMENT
        tx = Texture("../Content/Engine/brick.jpg");
        tx.load();
#endif
#endif
    }
    initEditor();
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

        glClearColor(rendererResources.colour.x, rendererResources.colour.y, rendererResources.colour.z, rendererResources.colour.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        UVK::Editor::beginFrame();
        level->gameMode->pawn->tick(deltaTime);
#ifdef DEVELOPMENT
        tx.useTexture();
#endif
    }
    else
    {
        glClearColor(rendererResources.colour.x, rendererResources.colour.y, rendererResources.colour.z, rendererResources.colour.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    UVK::GLEntityManager::tick(&level->gameMode->pawn->camera);

    glUseProgram(0);

    if (bEditor)
    {
#ifndef PRODUCTION
        UVK::GLFrameBuffer::unbindFramebuffer();
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ed.runEditor(rendererResources.colour, fb, level->gameMode->pawn->camera, level);
#endif
    }
    else
    {
        level->tick(deltaTime);
        events.callTick(deltaTime);
    }

    glfwSwapBuffers(currentWindow.getWindow());
}

void UVK::GLPipeline::end()
{
    if (bEditor)
    {
#ifndef PRODUCTION
        ed.destroyContext();
        level->gameMode->pawn->endPlay();
#endif
    }
    else
    {
        level->endPlay();
        events.callEnd();
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

void UVK::GLPipeline::initEditor()
{
    if (bEditor)
    {
#ifndef PRODUCTION
        ed.setTheme(colTheme);
        ed.initEditor();
#endif
    }
}

UVK::GLPipeline::GLPipeline(bool bHasEditor, UVK::Level *lvl)
{
    begin(bHasEditor, lvl);
}
