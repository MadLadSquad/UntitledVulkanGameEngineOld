#ifndef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include "VulkanRenderer.hpp"
#include "Renderer/EditorUI/Classes/EditorLevel.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <glfw3.h>
#include <Core/Events/Events.hpp>
#include <UVKShaderCompiler/Src/Functions.hpp>
#include <Renderer/Camera/Projection.hpp>
#include <Renderer/EditorUI/Editor.hpp>
#include <codecvt>

void UVK::VulkanRenderer::run() noexcept
{
    // Set the UVKShaderCompiler path and check for recompilation
    USC::setPrefixDir("../");
    USC::checkForCompile();

    std::cout << Locale::getLocaleString("The quick brown fox jumps over the lazy dog", LocaleTypes::jp_JP) << std::endl;

    global.window.createWindow();
    global.renderer = &renderer;
    renderer.create();

    Actor actor("Maikati", 10, "test");

    auto& mcomp = actor.add<MeshComponent>();
    mcomp.hue = { 1.0f, 1.0f, 1.0f, 1.0f };
    mcomp.create("../Content/Engine/teapot.obj", renderer.device, renderer.commands, renderer.descriptors);

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
        mcomp.translation = FVector(0.0f, sin(angle) - 0.75f, 0.0f);
        mcomp.rotation = FVector(0.0f, angle, 0.0f);
        mcomp.scale = FVector(0.025f, 0.025f, 0.025f);

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