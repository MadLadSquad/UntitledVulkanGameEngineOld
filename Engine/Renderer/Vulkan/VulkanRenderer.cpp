#ifndef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include "VulkanRenderer.hpp"
#include "Renderer/EditorUI/Classes/EditorLevel.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <glfw3.h>
#include <Core/Events/Events.hpp>
#include <Renderer/Camera/Projection.hpp>
#include <Renderer/EditorUI/Editor.hpp>
#include <codecvt>

void UVK::VulkanRenderer::run() noexcept
{
    global.window.createWindow();
    global.renderer = &renderer;
    renderer.create();

    Actor actor("Maikati", 10, "test");
    Actor actor2("Maikati2", 10, "test2");
    Actor actor3("Maikati3", 10, "test3");
    Actor actor4("Maikati4", 10, "test4");
    Actor actor5("Maikati5", 10, "test5");
    Actor actor6("Maikati6", 10, "test6");
    Actor actor7("Maikati7", 10, "test7");
    Actor actor8("Maikati8", 10, "test8");


    auto& mcomp = actor.add<MeshComponent>();
    mcomp.hue = { 1.0f, 1.0f, 1.0f, 1.0f };
    mcomp.create("../Content/Engine/generic_object_sphere.obj", renderer.device, renderer.commands, renderer.descriptors, actor.get<CoreComponent>());
//
    //auto& mcomp2 = actor2.add<MeshComponent>();
    //mcomp2.hue = { 1.0f, 1.0f, 1.0f, 1.0f };
    //mcomp2.create("../Content/Engine/generic_object_torus.obj", renderer.device, renderer.commands, renderer.descriptors, actor2.get<CoreComponent>());

    //auto& mcomp3 = actor3.add<MeshComponent>();
    //mcomp3.create("../Content/Engine/generic_object_monkey.obj", renderer.device, renderer.commands, renderer.descriptors, actor3.get<CoreComponent>());

    auto& mcomp4 = actor4.add<MeshComponent>();
    auto& core = actor4.get<CoreComponent>();
    mcomp4.create("../Content/Engine/generic_object_teapot.obj", renderer.device, renderer.commands, renderer.descriptors, core);

    auto& mcomp5 = actor5.add<MeshComponent>();
    mcomp5.create("../Content/Engine/generic_object_cylinder.obj", renderer.device, renderer.commands, renderer.descriptors, actor5.get<CoreComponent>());

    auto& mcomp6 = actor6.add<MeshComponent>();
    mcomp6.create("../Content/Engine/generic_object_cube.obj", renderer.device, renderer.commands, renderer.descriptors, actor6.get<CoreComponent>());

    auto& mcomp7 = actor7.add<MeshComponent>();
    mcomp7.create("../Content/Engine/generic_object_cone.obj", renderer.device, renderer.commands, renderer.descriptors, actor7.get<CoreComponent>());

    auto& mcomp8 = actor8.add<MeshComponent>();
    mcomp8.create("../Content/Engine/generic_object_pyramid.obj", renderer.device, renderer.commands, renderer.descriptors, actor8.get<CoreComponent>());

    beginEvents();

    double angle = 0.0f;
    double lastTime = 0.0f;
    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        static double deltaTime = 0.0f;
        glfwPollEvents();

        double now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        angle += ((angle + (1.0f * deltaTime)) >= 360.0f) ? -360.0f : 1.0f * deltaTime;
        //mcomp.translationOffset = FVector(0.0f, sin(angle) - 0.75f, 0.0f);
        //mcomp.rotationOffset = FVector(0.0f, angle, 0.0f);
        //mcomp.scaleOffset = FVector(-0.25f, -0.25f, -0.25f);
//
        //mcomp2.translationOffset = FVector(0.0f, -0.85f, 0.0f);
        //mcomp2.rotationOffset = FVector(0.0f, angle, 0.0f);

        //mcomp3.translationOffset = FVector(-5.0f, 3.0f, 0.0f);
        //mcomp3.rotationOffset = FVector(angle * 0.5f, 0.0f, 135.0f);

        mcomp4.translationOffset = FVector(5.0f, 2.75f, 0.0f);
        mcomp4.rotationOffset = FVector(angle, 0.0f, 45.0f);
        core.scale = FVector(0.020f, 0.020f, 0.020f);

        mcomp5.translationOffset = FVector(-5.0f, -3.0f, 0.0f);
        mcomp5.rotationOffset = FVector(angle * 1.5f, 0.0f, 135.0f);

        mcomp6.translationOffset = FVector(5.0f, -3.0f, 0.0f);
        mcomp6.rotationOffset = FVector(angle * 0.5f, 0.0f, 45.0f);

        mcomp7.translationOffset = FVector(-5.0f, 0.0f, 0.0f);
        mcomp7.rotationOffset = FVector(angle, 0.0f, 135.0f);

        mcomp8.translationOffset = FVector(5.0f, 0.0f, 0.0f);
        mcomp8.rotationOffset = FVector(angle * 1.5f, 0.0f, 45.0f);

        global.instance->initInfo.shaderConstantStruct.data->lightPosition = FVector4(0.0f, 0.0f, -0.5f, 0.0f);
        updateEvents(deltaTime);
        renderer.commands.draw();
    }
    destroyEvents();
    renderer.destroy();
}

void UVK::VulkanRenderer::updateEvents(double deltaTime) noexcept
{
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
        //global.ui.update();
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
        //ed.runEditor(global.colour, UVK::Level::getPawn(UVK::global.currentLevel)->camera, global.currentLevel, deltaTime);
    }
#endif
    global.finalizeOpening();
}

void UVK::VulkanRenderer::beginEvents() noexcept
{
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
            global.currentLevel->gameMode = GameMode::makeGameMode<EditorGameMode>();
        if (UVK::Level::getPawn(UVK::global.currentLevel) == nullptr)
            global.currentLevel->gameMode->playerController->pawn = Pawn::makePawn<EditorPawn>();
#endif
        //global.ui.init();
        global.instance->beginPlay();
        global.currentLevel->beginPlay();
    }
}

void UVK::VulkanRenderer::destroyEvents() noexcept
{
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
}

void UVK::InternalRendererComponents::create() noexcept
{
    instance = VKInstance{};
    device = VKDevice(instance);
    swapchain = Swapchain(instance, device);
    descriptors = VKDescriptors(device, swapchain, resources);
    depthBuffer = VKDepthBuffer{};
    pipeline = GraphicsPipeline(device, swapchain, descriptors, depthBuffer);
    swapchain.setDepthBuffer(depthBuffer);

    instance.create();
    swapchain.createSurface();
    device.createDevice(swapchain);
    swapchain.createSwapchain();
    swapchain.createMultisampledImage();
    depthBuffer.createDepthBufferImage(swapchain, device);
    pipeline.createRenderPass();
    descriptors.createDescriptorSetLayout();
    pipeline.createGraphicsPipeline();
    swapchain.createFramebuffers(pipeline);

    resources = VKResources(device);
    commands = Commands(device, swapchain, pipeline, descriptors, resources);
    commands.createCommandPool();

    commands.createCommandBuffers(swapchain.getFramebuffers().size());
    resources.allocateDynamicUniformBufferTransferSpace();
    resources.createUniformBuffers(swapchain.getFramebuffers().size());

    descriptors.createDescriptorPool();
    descriptors.createDescriptorSets();
    commands.createSynchronization();
}

void UVK::InternalRendererComponents::destroy() noexcept
{
    vkDeviceWaitIdle(device.getDevice());
    global.ecs.clear();
    descriptors.destroyTextureDescriptor();
    depthBuffer.destroyDepthBufferImage(device);
    swapchain.destroyMultisampledImage();
    resources.freeDynamicUniformBufferTransferSpace();
    descriptors.destroyDescriptorPool();
    resources.destroyUniformBuffers();
    pipeline.destroyGraphicsPipeline();
    descriptors.destroyDescriptorSetLayout();

    commands.destroySynchronization();
    commands.destroyCommandBuffers();
    commands.destroyCommandPool();
    swapchain.destroyFramebuffers();

    swapchain.destroySwapchain();
    swapchain.destroySurface();
    device.destroyDevice();
    instance.destroy();
}

void UVK::InternalRendererComponents::recreate() noexcept
{
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(global.window.getWindow(), &width, &height);

    while (width == 0 && height == 0)
    {
        glfwGetFramebufferSize(global.window.getWindow(), &width, &height);
        glfwWaitEvents();
    }
    global.window.resized() = false;
    vkDeviceWaitIdle(device.getDevice());
    commands.destroyCommandBuffers();
    commands.destroyCommandPool();
    swapchain.destroyFramebuffers();
    pipeline.destroyGraphicsPipeline();
    depthBuffer.destroyDepthBufferImage(device);
    swapchain.destroyMultisampledImage();
    swapchain.destroySwapchain(true);

    swapchain.createSwapchain(swapchain.getSwapchain());
    swapchain.createMultisampledImage();
    depthBuffer.createDepthBufferImage(swapchain, device);
    pipeline.createRenderPass();
    pipeline.createGraphicsPipeline();
    swapchain.createFramebuffers(pipeline);
    commands.createCommandPool();
    commands.createCommandBuffers(swapchain.getFramebuffers().size());
}
#endif