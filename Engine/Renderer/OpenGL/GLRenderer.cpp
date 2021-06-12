// GLRenderer.cpp
// Last update 20/5/2021 by Madman10K
#include <GL/glew.h>
#include "GLRenderer.hpp"
#include "../OpenGL/Components/GLMesh.hpp"
#include "../OpenGL/Components/GLCamera.hpp"
#include "../../Core/Events/Events.hpp"
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"
#include "Engine/Core/Core/Registry.hpp"

void UVK::GLRenderer::renderEditor()
{

}

void UVK::GLRenderer::initEditor() {
    if (bEditor)
    {
        ed.setTheme(colTheme);
        ed.initEditor();
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
}

void UVK::GLRenderer::createWindow(UVK::Level* level) noexcept
{
    // if the editor is running we will assign this pointer to an editor camera otherwise
    // it will point to the active pawn's camera
    GLCamera* cm = nullptr;
    if (bEditor)
    {
        cm = new GLCamera(FVector(-10.0f, 0.0f, 15.0f), FVector(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
    }
    else
    {
        cm = new GLCamera(FVector(-10.0f, 0.0f, 15.0f), FVector(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
    }

    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f
    };

    currentWindow.createWindow();

    logger.consoleLog("Creating geometry", UVK_LOG_TYPE_NOTE);
    


    registry.createActor("Maikati");
    pool.each([&](entt::entity ent){
        if (registry.getComponent<CoreComponent>(ent).name == "Maikati")
        {
            registry.getComponent<CoreComponent>(ent).devName = "a";
            auto& a = registry.addComponent<MeshComponentRaw>(ent);
            a.createMesh(vertices, indices, 20, 12, "../Content/Engine/defaultvshader.gl", "../Content/Engine/defaultfshader.gl", SHADER_IMPORT_TYPE_FILE);
            a.rotation = FVector(0.0f, 0.0f, 0.0f);
            //auto& b = registry.addComponent<AudioComponent3D>(ent);
            //b.play("and.wav", true, 1.0f, 1.0f, FVector(15.0f, 0.0f, 0.0f));
        }
    });

    projection = glm::perspective(glm::radians(120.0f), (GLfloat)currentWindow.getBufferWidth() / (GLfloat)currentWindow.getBufferHeight(), 0.1f, 100.0f);

    initEditor();

    logger.consoleLog("Init editor", UVK_LOG_TYPE_SUCCESS);

    if (!bEditor)
    {
        events.callBegin();
    }
    
    GLfloat deltaTime;
    GLfloat lastTime = 0;
    
    colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);

    Texture tx("../Content/Engine/brick.jpg");
    tx.load();

    while (!glfwWindowShouldClose(currentWindow.getWindow()))
    {
        glfwPollEvents();

        auto now = (float)glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        if (bEditor)
        {
            cm->move(deltaTime);
            cm->moveMouse(deltaTime, UVK::Input::getMousePositionChange());

            fb.useFramebuffer();
            glEnable(GL_DEPTH_TEST);

            glClearColor(colour.x, colour.y, colour.z, colour.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            UVK::Editor::beginFrame();
        }
        else
        {
            glClearColor(colour.x, colour.y, colour.z, colour.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }

        pool.each([&](entt::entity ent)
        {
            if (registry.hasComponent<AudioComponent>(ent))
            {
#ifndef __MINGW32__
                bool bRemove = false;

                {
                    auto& audiocmp = registry.getComponent<AudioComponent>(ent);

                    auto& state = audiocmp.src.getState();

                    if (state == UVK_AUDIO_STATE_RESUME)
                    {
                        audiocmp.src.play();
                    }
                    else if (state == UVK_AUDIO_STATE_PAUSED)
                    {
                        alSourcePause(audiocmp.src.getBuffer().getBuffer());
                    }
                    else if (state == UVK_AUDIO_STATE_STOPPED)
                    {
                        audiocmp.src.getBuffer().removeSound();
                        bRemove = true;
                    }
                }
                if (bRemove)
                {
                    registry.removeComponent<AudioComponent>(ent);
                }
#endif
            }

            if (registry.hasComponent<MeshComponentRaw>(ent))
            {
                auto& a = registry.getComponent<MeshComponentRaw>(ent);
                tx.useTexture();
                a.render(projection, *cm);
            }
        });
        glUseProgram(0);

        if (bEditor)
        {
            UVK::GLFrameBuffer::unbindFramebuffer();
            glDisable(GL_DEPTH_TEST);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            ed.runEditor(colour, fb, *cm, projection);
        }
        else
        {
            level->tick(deltaTime);
            events.callTick(deltaTime);
        }

        glfwSwapBuffers(currentWindow.getWindow());
    }

    if (bEditor)
    {
        ed.destroyContext();
    }
    else
    {
        events.callEnd();
    }

    pool.each([&](entt::entity ent)
    {
        if (registry.hasComponent<MeshComponentRaw>(ent))
        {
            auto& a = registry.getComponent<MeshComponentRaw>(ent);

            a.clearMesh();
        }

        if (registry.hasComponent<AudioComponent>(ent))
        {
#ifndef __MINGW32__
            auto& a = registry.getComponent<AudioComponent>(ent);

            a.src.getBuffer().removeSound();
#endif
        }
    });

    pool.clear();
}
