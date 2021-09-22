// EditorViewport.cpp
// Last update 22/9/2021 by Madman10K
#include <GL/glew.h>
#include <Engine/Core/Core/Global.hpp>
#include <Renderer/Window/Window.hpp>
#include "EditorViewport.hpp"
#include <imgui.h>
#include <imguiex/imguizmo/ImGuizmo.h>
#include <Core/Actor.hpp>
#include <GameFramework/Components/Components.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>

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
        UVK::Level::getPawn(UVK::global.currentLevel)->camera.projection().aspectRatio() = ImGui::GetWindowWidth() / ImGui::GetWindowHeight();
    }
    ImGui::Image((void*)(intptr_t)fb.getFramebufferTexture(), ImVec2((float)viewportWidth, (float)viewportHeight), ImVec2(0, 1), ImVec2(1, 0));

    static int16_t operationType = -1;
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
            operationType = ImGuizmo::SCALEU;
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

    if (entity.has<UVK::CoreComponent>() && operationType != -1)
    {
        auto& core = entity.get<UVK::CoreComponent>();

        const float snapValues[3] = { snapVal, snapVal, snapVal };
        UVK::FVector translation, rotation, scale, deltaRotation;

        ImGuizmo::SetOrthographic(false);
        ImGuizmo::AllowAxisFlip(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

        glm::mat4 mat(1.0f);
        UVK::Math::translate(mat, core.translation);
        UVK::Math::rotate(mat, core.rotation);
        UVK::Math::scale(mat, core.scale);

        ImGuizmo::Manipulate(glm::value_ptr(camera.calculateViewMatrixRH()), glm::value_ptr(projection), (ImGuizmo::OPERATION)operationType, ImGuizmo::LOCAL, glm::value_ptr(mat), nullptr, snap ? snapValues : nullptr);

        if (ImGuizmo::IsUsing())
        {
            ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(mat), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));

            deltaRotation = glm::radians(rotation) - core.rotation;

            core.translation = translation;
            core.rotation += deltaRotation;
            core.scale = scale;
        }
    }
    ImGui::End();
}
#endif