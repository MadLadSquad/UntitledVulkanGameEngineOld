// UI.cpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include "UI.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>
#include <Core/Global.hpp>

void UVK::UI::init()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = "gameui.ini";

    ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 1.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    if (global.bUsesVulkan)
    {
        ImGui_ImplGlfw_InitForVulkan(global.window.getWindow(), true);
        // Info to be passed by the Vulkan renderer
        //ImGui_ImplVulkan_Init(nullptr);
    }
    else
    {
        ImGui_ImplGlfw_InitForOpenGL(global.window.getWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 450");
    }
}

void UVK::UI::update()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    window_flags |=  ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowBgAlpha(1.0f);
    ImGui::SetNextWindowPos(viewport->GetWorkPos());
    ImGui::SetNextWindowSize(viewport->GetWorkSize());
    ImGui::SetNextWindowViewport(viewport->ID);

    bool bIsOpen = true;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Workspace", &bIsOpen, window_flags);
    ImGui::PopStyleVar(1);

    renderUI();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void UVK::UI::clean()
{
    if (global.bUsesVulkan)
    {
        ImGui_ImplVulkan_Shutdown();
    }
    else
    {
        ImGui_ImplOpenGL3_Shutdown();
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UVK::UI::beginFrame()
{
    if (global.bUsesVulkan)
    {
        ImGui_ImplVulkan_NewFrame();
    }
    else
    {
        ImGui_ImplOpenGL3_NewFrame();
    }
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UVK::UI::renderUI()
{
    for (auto& a : eventArr)
    {
        a();
    }

    for (auto& a : eventArrImGui)
    {
        a();
    }
}

void UVK::UI::addEvent(const std::function<void(void)>& func)
{
    eventArr.push_back(func);
}

void UVK::UI::addEventImgui(const std::function<void(void)>& func)
{
    eventArrImGui.push_back(func);
}

void UVK::UI::clear()
{
    eventArr.clear();
    eventArrImGui.clear();
}
