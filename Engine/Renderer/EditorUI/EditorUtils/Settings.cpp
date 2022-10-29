#include "Settings.hpp"
#include <imgui.h>
#include "../Style/Theme.hpp"
#include <imguiex/implot/implot.h>
#include <Core/Global.hpp>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#include <glfw3.h>
#include <Renderer/EditorUI/Editor.hpp>
#include <Renderer/Vulkan/VulkanRenderer.hpp>

void UVK::EditorUtilSettings::loadImGuiSettings(Editor& editor, const char* colTheme, InternalRendererComponents& renderer) noexcept
{
    constexpr VkDescriptorPoolSize poolSizes[] =
    {
         { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
         { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
         { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
         { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
         { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
         { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
         { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
         { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
         { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
         { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    };

    const VkDescriptorPoolCreateInfo poolCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
        .maxSets = 1000,
        .poolSizeCount = 11,
        .pPoolSizes = poolSizes
    };

    VkDescriptorPool imguiPool;
    auto result = vkCreateDescriptorPool(renderer.device.getDevice(), &poolCreateInfo, nullptr, &imguiPool);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't create the descriptor pool for Dear imgui! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    ImGui::CreateContext();
    ImPlot::CreateContext();
    //ImTTY::Terminal.CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    io.ConfigViewportsNoTaskBarIcon = true;
    ImGui::LoadIniSettingsFromDisk((editor.settings.editorLayoutLocation + ".ini").c_str());

    ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    ImGuiStyle& style = ImGui::GetStyle();
    EditorTheme theme;
    if (!global.rendererSettings.themeLoc.empty())
        theme = EditorTheme(colTheme);

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    if (!global.rendererSettings.themeLoc.empty())
    {
        theme.useTheme();
        style.WindowRounding = theme.getWindowRounding();
#ifndef __MINGW32__
        if (std_filesystem::exists(theme.getFont().first.c_str()))
        {
            ImFontConfig config;
            io.Fonts->AddFontFromFileTTF(theme.getFont().first.c_str(), (float)theme.getFont().second, &config, io.Fonts->GetGlyphRangesCyrillic());
            io.Fonts->AddFontFromFileTTF(theme.getFont().first.c_str(), (float)theme.getFont().second, &config, io.Fonts->GetGlyphRangesThai());
            io.Fonts->AddFontFromFileTTF(theme.getFont().first.c_str(), (float)theme.getFont().second, &config, io.Fonts->GetGlyphRangesVietnamese());

            io.Fonts->Build();
        }
#endif
    }

    ImGui_ImplVulkan_InitInfo initInfo =
    {
        .Instance = renderer.instance.data(),
        .PhysicalDevice = renderer.device.getPhysicalDevice(),
        .Device = renderer.device.getDevice(),
        .QueueFamily = static_cast<uint32_t>(renderer.device.getIndices().graphicsFamily),
        .Queue = renderer.device.getGraphicsQueue(),
        .DescriptorPool = imguiPool,
        .MinImageCount = 3,
        .ImageCount = 3,
        .MSAASamples = static_cast<VkSampleCountFlagBits>(global.rendererSettings.samples)
    };

    //ImGui_ImplVulkan_CreateFontsTexture(cmd);
    ImGui_ImplVulkan_DestroyFontUploadObjects();


    ImGui_ImplGlfw_InitForVulkan(global.window.getWindow(), true);
    ImGui_ImplVulkan_Init(&initInfo, renderer.pipeline.getRenderPass());
}

void UVK::EditorUtilSettings::setImGuiSettings(Editor& editor) noexcept
{
    static bool opt_fullscreen = true;
    static bool bIsOpen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
    }
    else
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;


    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &bIsOpen, window_flags | ImGuiWindowFlags_NoCollapse);

    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
}

void UVK::EditorUtilSettings::finishImGuiRender(UVK::Editor& editor, uint32_t currentImage) noexcept
{
    ImGui::Render();

    if (global.bUsesVulkan)
    {
        // To be implemented
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), global.renderer->commands.getCommandBuffers()[currentImage], global.renderer->pipeline.getPipeline());
    }
    else
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
