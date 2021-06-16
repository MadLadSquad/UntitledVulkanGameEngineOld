// EditorViewport.cpp
// Last update 15/6/2021 by Madman10K
#include <GL/glew.h>
#include <Renderer/Window/Window.hpp>
#include "EditorViewport.hpp"
#include <imgui.h>
#include <imguiex/imguizmo/ImGuizmo.h>
#include <Core/Registry.hpp>
#ifndef PRODUCTION
void EditorViewport::display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight, bool& bShow, UVK::GLCamera& camera, UVK::Actor& entity, glm::mat4& projection)
{
    ImGui::Begin("Viewport##1", &bShow);

    if (viewportWidth != (int)ImGui::GetWindowWidth() || viewportHeight != (int)ImGui::GetWindowHeight())
    {
        UVK::GLFrameBuffer::unbindFramebuffer();
        fb.destroyFramebuffer();

        glViewport(0, 0, (int)ImGui::GetWindowWidth(), (int)ImGui::GetWindowHeight());
        fb.init((int)ImGui::GetWindowWidth(), (int)ImGui::GetWindowHeight());
        viewportWidth = (int)ImGui::GetWindowWidth();
        viewportHeight = (int)ImGui::GetWindowHeight();
    }
    ImGui::Image((void*)(intptr_t)fb.getFramebufferTexture(), ImVec2((float)viewportWidth, (float)viewportHeight), ImVec2(0, 1), ImVec2(1, 0));

    static int operationType = -1;
    bool snap;
    float snapVal = 0.05f;

    if (UVK::Input::getKeyPressed(Keys::LeftControl) && UVK::Input::getKeyPressed(Keys::Q))
    {
        operationType = -1;
    }
    else if (UVK::Input::getKeyPressed(Keys::LeftControl) && UVK::Input::getKeyPressed(Keys::W))
    {
        operationType = ImGuizmo::TRANSLATE;
    }
    else if (UVK::Input::getKeyPressed(Keys::LeftControl) && UVK::Input::getKeyPressed(Keys::E))
    {
        operationType = ImGuizmo::ROTATE;
    }
    else if (UVK::Input::getKeyPressed(Keys::LeftControl) && UVK::Input::getKeyPressed(Keys::R))
    {
        operationType = ImGuizmo::SCALE;
    }

    snap = UVK::Input::getKeyPressed(Keys::LeftControl);

    if (operationType == ImGuizmo::ROTATE) snapVal = 10.0f;

    if (registry.hasComponent<UVK::MeshComponentRaw>(entity) && operationType != -1)
    {
        auto& a = registry.getComponent<UVK::MeshComponentRaw>(entity);

        const float snapValues[3] = { snapVal, snapVal, snapVal };

        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

        ImGuizmo::Manipulate(glm::value_ptr(camera.calculateViewMatrix()), glm::value_ptr(projection), (ImGuizmo::OPERATION)operationType, ImGuizmo::LOCAL, glm::value_ptr(a.mat), nullptr, snap ? snapValues : nullptr);

        if (ImGuizmo::IsUsing())
        {
            UVK::FVector translation, rotation, scale, deltaRotation;
            ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(a.mat), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));

            deltaRotation = glm::radians(rotation) - a.rotation;

            a.translation = translation;
            a.rotation += deltaRotation;
            a.scale = scale;
        }
    }
    else if (registry.hasComponent<UVK::MeshComponent>(entity) && operationType != -1)
    {
        //todo add the functionality for a regular mesh component
    }
    else if (registry.hasComponent<UVK::AudioComponent>(entity) && operationType != -1)
    {
        auto& a = registry.getComponent<UVK::AudioComponent>(entity);

        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

        //ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform));

        if (ImGuizmo::IsUsing())
        {

        }
    }
    ImGui::End();
}
#endif