// EditorViewport.cpp
// Last update 19/6/2021 by Madman10K
#include <GL/glew.h>
#include <Renderer/Window/Window.hpp>
#include "EditorViewport.hpp"
#include <imgui.h>
#include <imguiex/imguizmo/ImGuizmo.h>
#include <Core/Registry.hpp>
#ifndef PRODUCTION
void EditorViewport::display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight, bool& bShow, UVK::Camera& camera, UVK::Actor& entity, glm::mat4& projection)
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

    if (UVK::Input::getAction("editor-gizmos") == Keys::KeyPressed || UVK::Input::getAction("editor-gizmos") == Keys::KeyRepeat)
    {
        if (UVK::Input::getAction("editor-gizmo-none") == Keys::KeyPressed || UVK::Input::getAction("editor-gizmo-none") == Keys::KeyRepeat)
        {
            operationType = -1;
        }
        else if (UVK::Input::getAction("editor-gizmo-translate") == Keys::KeyPressed || UVK::Input::getAction("editor-gizmo-translate") == Keys::KeyRepeat)
        {
            operationType = ImGuizmo::TRANSLATE;
        }
        else if (UVK::Input::getAction("editor-gizmo-rotate") == Keys::KeyPressed || UVK::Input::getAction("editor-gizmo-rotate") == Keys::KeyRepeat)
        {
            operationType = ImGuizmo::ROTATE;
        }
        else if (UVK::Input::getAction("editor-gizmo-scale") == Keys::KeyPressed || UVK::Input::getAction("editor-gizmo-scale") == Keys::KeyRepeat)
        {
            operationType = ImGuizmo::SCALE;
        }
    }

    snap = UVK::Input::getAction("editor-gizmo-snap") == Keys::KeyPressed;

    switch (operationType)
    {
    case ImGuizmo::TRANSLATE:
        snapVal = 0.1f;
        break;
    case ImGuizmo::ROTATE:
        snapVal = 10.0f;
        break;
    case ImGuizmo::SCALE:
        snapVal = 0.05f;
        break;
    default:
        break;
    }

    if (registry.hasComponent<UVK::MeshComponentRaw>(entity) && operationType != -1)
    {
        auto& a = registry.getComponent<UVK::MeshComponentRaw>(entity);

        const float snapValues[3] = { snapVal, snapVal, snapVal };
        UVK::FVector translation, rotation, scale, deltaRotation;

        ImGuizmo::SetOrthographic(false);
        ImGuizmo::AllowAxisFlip(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

        ImGuizmo::Manipulate(glm::value_ptr(camera.calculateViewMatrixRH()), glm::value_ptr(projection), (ImGuizmo::OPERATION)operationType, ImGuizmo::LOCAL, glm::value_ptr(a.mat), nullptr, snap ? snapValues : nullptr);

        if (ImGuizmo::IsUsing())
        {
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