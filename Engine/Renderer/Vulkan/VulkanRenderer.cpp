#ifndef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include "VulkanRenderer.hpp"
#include "Renderer/EditorUI/Classes/EditorLevel.hpp"
#include "VKEntityManager.hpp"
#include "Components/Instance.hpp"
#include "Components/Device.hpp"
#include "Components/Swapchain.hpp"
#include "Components/GraphicsPipeline.hpp"
#include "Components/Descriptors.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <glfw3.h>
#include <Core/Events/Events.hpp>
#include <UVKShaderCompiler/Src/Functions.hpp>
#include "Components/VKMesh.hpp"
#include <Renderer/Camera/Projection.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <Renderer/EditorUI/Editor.hpp>

void UVK::VulkanRenderer::run() noexcept
{
    // Set the UVKShaderCompiler path and check for recompilation
    USC::setPrefixDir("../");
    USC::checkForCompile();

    global.window.createWindow();

    VKInstance instance{};
    Swapchain swapchain{};
    VKDevice device(instance);
    swapchain = Swapchain(instance, device);
    VKDescriptors descriptors(device, swapchain, swapchain.getResources());
    GraphicsPipeline pipeline(device, swapchain, descriptors);


    instance.create();
    swapchain.createSurface();
    device.createDevice(swapchain);
    swapchain.createSwapchain();
    pipeline.createRenderPass();
    descriptors.createDescriptorSetLayout();
    pipeline.createGraphicsPipeline();
    swapchain.createFramebuffers(pipeline);

    VP mvp =
    {
            .view = glm::lookAt(FVector(0.0f, 0.0f, -5.0f), FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f)),
            .projection = glm::perspective(glm::radians(45.0f), (float)swapchain.getExtent().width / (float)swapchain.getExtent().height, 0.1f, 100.0f),
    };

    std::vector<VKVertex> vertices =
    {
            {{-0.8f, -0.5f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}},
            {{0.3f, 0.5f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{-0.8f, 0.5f, 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f}},
            {{0.3f, -0.5f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}},
    };
    std::vector<VKVertex> vertices2 =
    {
            {{0.4f, -0.5f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}},
            {{0.9f, 0.5f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{0.4f, 0.5f, 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f}},
            {{0.9f, -0.5f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}},
    };
    std::vector<uint32_t> indices =
    {
            0, 1, 2,
            0, 3, 1
    };

    Actor actor("Maikati", 10, "test");
    Actor actor2("Maikati2", 11, "test2");

    auto& mcomp = actor.add<MeshComponentRaw>();
    mcomp.create(vertices, indices, device, swapchain.getCommands());

    auto& mcomp2 = actor2.add<MeshComponentRaw>();
    mcomp2.create(vertices2, indices, device, swapchain.getCommands());


    //VKMesh mesh(device, device.getGraphicsQueue(), swapchain.getCommandPool(), vertices, indices);
    //VKMesh mesh2(device, device.getGraphicsQueue(), swapchain.getCommandPool(), vertices2, indices);
    //std::vector<VKMesh> meshes = { mesh, mesh2 };
    swapchain.getCommands().createCommandBuffers(swapchain.getFramebuffers().size());
    swapchain.getResources().allocateDynamicUniformBufferTransferSpace();
    swapchain.getResources().createUniformBuffers(swapchain.getFramebuffers().size());
    descriptors.createDescriptorPool();
    descriptors.createDescriptorSets();
    swapchain.getCommands().createSynchronization();

    double angle = 0.0f;
    double deltaTime;
    double lastTime = 0.0f;

    if (global.bEditor)
    {
#ifndef PRODUCTION
        delete global.currentLevel;
        auto* lv = new UVK::EditorLevel;
        global.currentLevel = lv;
        global.currentLevel->beginPlay();

        colTheme = global.rendererSettings.themeLoc.c_str();
        //ed.setTheme(colTheme);
        //ed.initEditor();
        //global.instance->onEventInitEditorModules(); // Always call after the editor is instantiated
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
        //global.ui.init();
        global.instance->beginPlay();
        global.currentLevel->beginPlay();
    }

    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        glfwPollEvents();

        double now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        //mcomp.rotation = FVector(0.0f, 180.0f, 0.0f);

        //angle += 1.0f * deltaTime;
//
        //mcomp.translation = FVector(-1.5f, 0.0f, 0.0f);
        //mcomp.rotation = FVector(0.0f, 0.0f, angle);
        //meshes[0].model.model = glm::mat4(1.0f);
        //Math::translate(meshes[0].model.model, FVector(-1.5f, 0.0f, 0.0f));
        //Math::rotate(meshes[0].model.model, FVector(0.0f, 0.0f, angle));
#ifndef PRODUCTION
        if (global.bEditor)
        {
            //UVK::Editor::beginFrame();
            global.currentLevel->tick(static_cast<float>(deltaTime));
        }
        else
        {
            //UVK::UIInternal::beginFrame();

            global.currentLevel->tick(static_cast<float>(deltaTime));
            Events::callTick(static_cast<float>(deltaTime));
            global.ui.update();
        }
#else
        //UVK::UIInternal::beginFrame();

        global.currentLevel->tick(deltaTime);
        Events::callTick(deltaTime);
        //global.ui.update();
#endif

#ifndef PRODUCTION
        if (global.bEditor)
        {
            //ed.runEditor(global.colour, fb, UVK::Level::getPawn(UVK::global.currentLevel)->camera, global.currentLevel, deltaTime);
        }
#endif
        global.finalizeOpening();

        swapchain.getCommands().draw();
    }
    if (global.bEditor)
    {
#ifndef PRODUCTION
        //ed.destroyContext();
        UVK::Level::getPawn(UVK::global.currentLevel)->endPlay();
#endif
    }
    else
    {
        global.currentLevel->endPlay();
        Events::callEnd();
        global.instance->endPlay();
        //UVK::UIInternal::clean();
        global.window.destroyWindow();
    }
    //UVK::GLEntityManager::clean();
    vkDeviceWaitIdle(device.getDevice());
    global.ecs.clear();
    swapchain.getResources().freeDynamicUniformBufferTransferSpace();
    descriptors.destroyDescriptorPool();
    swapchain.getResources().destroyUniformBuffers();
    descriptors.destroyDescriptorSetLayout();

    swapchain.destroyFramebuffers();
    swapchain.destroySwapchain();
}
#endif