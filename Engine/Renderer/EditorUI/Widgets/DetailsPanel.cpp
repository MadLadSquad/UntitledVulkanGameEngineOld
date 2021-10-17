// DetailsPanel.cpp
// Last update 17/10/2021 by Madman10K
#include "DetailsPanel.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <GameFramework/Components/Components.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Renderer/EditorUI/Modules/EditorModule.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>

bool DetailsPanel::DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue, float columnWidth)
{
    const ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushItemWidth(50);
    ImGui::PushItemWidth(50);
    ImGui::PushItemWidth(50);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    bool x = false;
    bool y = false;
    bool z = false;

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
    {
        if (values.x != resetValue)
        {
            values.x = resetValue;
            x = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    if (ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f") || (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)))
        x = true;

    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
    {
        if (values.y != resetValue)
        {
            values.y = resetValue;
            y = false;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    if (ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f") || (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)))
        y = true;

    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize))
    {
        if (values.z != resetValue)
        {
            values.z = resetValue;
            z = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    if (ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f") || (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)))
        z = true;
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();

    return x || y || z;
}

bool DetailsPanel::display(UVK::Actor& ent, UVK::Level* lvl, bool& bShow, const UVK::EditorModuleManager& modules, bool& destroy)
{
    bool bReturn = false;
    ImGui::Begin("Details", &bShow, ImGuiWindowFlags_MenuBar);
    if (ent.valid())
    {
        ImGui::BeginMenuBar();

        if (ImGui::BeginMenu("+ Add Component"))
        {
            if (ImGui::MenuItem("Raw Mesh"))
            {
                addComponent<UVK::MeshComponentRaw>(ent);
            }

            if (ImGui::MenuItem("Mesh"))
            {
                addComponent<UVK::MeshComponent>(ent);
            }

            //if (ImGui::MenuItem("Audio"))
            //{
            //    if (!ent.has<UVK::AudioComponent>())
            //    {
            //        auto& a = ent.add<UVK::AudioComponent>();

            //        UVK::AudioSourceData dt;
            //        dt.location = "test.wav";
            //        dt.velocity = UVK::FVector(0.0f, 0.0f, 0.0f);
            //        dt.position = UVK::FVector(0.0f, 0.0f, 0.0f);
            //        dt.bLoop = false;
            //        dt.gain = 1.0f;
            //        dt.pitch = 1.0f;
            //        a.init(dt);
            //    }
            //}

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("- Remove Component"))
        {
            if (ImGui::MenuItem("Raw Mesh##rm"))
            {
                removeComponent<UVK::MeshComponentRaw>(ent);
            }

            if (ImGui::MenuItem("Mesh##rm"))
            {
                removeComponent<UVK::MeshComponent>(ent);
            }

            //if (ImGui::MenuItem("Audio##rm"))
            //{
            //    if (ent.has<UVK::AudioComponent>())
            //    {
            //        ent.remove<UVK::AudioComponent>();
            //    }
            //}

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();

        if (UVK::ECS::data().any_of<UVK::CoreComponent>(ent.data()))
        {
            auto& a = ent.get<UVK::CoreComponent>();

            ImGui::TextWrapped("Name");
            ImGui::SameLine();
            if (ImGui::InputText("##Name##inputactorname", &a.name) || ImGui::IsItemFocused())
                bReturn = true;

            ImGui::TextWrapped("ID");
            ImGui::SameLine();
            if (ImGui::InputScalar("##ID##inputactoridentifier", ImGuiDataType_U64, &a.id) || ImGui::IsItemFocused())
                bReturn = true;
            if (a.id == 330 && a.name.find("Editor") == std::string::npos)
                a.id += 1;

            ImGui::TextWrapped("Development Name");
            ImGui::SameLine();
            if (ImGui::InputText("##Development Name##devname", &a.devName) || ImGui::IsItemFocused())
                bReturn = true;

            DrawVec3Control("Translation", a.translation, 0.0f, 100.0f);
            DrawVec3Control("Rotation", a.rotation, 0.0f, 100.0f);
            DrawVec3Control("Scale", a.scale, 1.0f, 100.0f);

            if (a.name == UVK::Level::getPawn(lvl)->name && a.id == UVK::Level::getPawn(lvl)->id && a.devName == UVK::Level::getPawn(lvl)->devName)
            {
                ImGui::Separator();

                static float FOV = UVK::Level::getPawn(lvl)->camera.projection().fov();
                static UVK::FVector2 planes = UVK::Level::getPawn(lvl)->camera.projection().planes();
                ImGui::TextWrapped("Camera FOV");
                ImGui::SameLine();
                ImGui::SliderFloat("##Camera FOV fov", &FOV, 1.0f, 180.0f);
                ImGui::TextWrapped("Near Plane");
                ImGui::SameLine();
                ImGui::SliderFloat("##Near Plane plane", &planes.x, 0.01f, 10000);
                ImGui::TextWrapped("Far Plane");
                ImGui::SameLine();
                ImGui::SliderFloat("##Far Plane plane", &planes.y, 0.01f, 10000);

                float& ar = UVK::Level::getPawn(lvl)->camera.projection().aspectRatio();
                static UVK::FVector2 aspect = UVK::FVector2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

                ImGui::TextWrapped("Aspect Ratio");
                ImGui::SameLine();
                ImGui::DragFloat2("##Aspect Ratio ratio", glm::value_ptr(aspect), 1.0f, 0.01f);

                if ((aspect.x / aspect.y) != ar || FOV != UVK::Level::getPawn(lvl)->camera.projection().fov() || planes != UVK::Level::getPawn(lvl)->camera.projection().planes())
                {
                    UVK::Level::getPawn(lvl)->camera.projection().fov() = FOV;
                    UVK::Level::getPawn(lvl)->camera.projection().planes() = planes;
                    ar = aspect.x / aspect.y;
                    UVK::Level::getPawn(lvl)->camera.projection().recalculateRH();
                }
                UVK::Level::getPawn(lvl)->camera.recalculate();
            }
        }

        //if (ent.has<UVK::MeshComponentRaw>())
        //{
        //    ImGui::Separator();
//
        //    auto& cmp = ent.get<UVK::MeshComponentRaw>();
        //}

#ifndef __MINGW32__
        if (ent.has<UVK::AudioComponent>())
        {
            ImGui::Separator();

            auto& cmp = ent.get<UVK::AudioComponent>();
            //UVK::AudioSourceData dt = cmp.data;

            //ImGui::TextWrapped("Pitch");
            //ImGui::SameLine();
            //ImGui::SliderFloat("##Pitchpt", &dt.pitch, 0.5f, 2.0f);
//
            //ImGui::TextWrapped("Gain");
            //ImGui::SameLine();
            //ImGui::SliderFloat("##Gaingn", &dt.gain, 0.0f, 10.0f);
//
            //ImGui::TextWrapped("Repeat");
            //ImGui::SameLine();
            //ImGui::Checkbox("##Repeatrt", &dt.bLoop);
//
            //ImGui::TextWrapped("File Location");
            //ImGui::SameLine();
            //ImGui::InputText("##File Location fl", &dt.location);
//
            //cmp.data = dt;
            //if (ImGui::Button("Play") && !dt.location.empty())
            //{
            //    ent.remove<UVK::AudioComponent>();
            //    auto& comp = ent.add<UVK::AudioComponent>();
            //    comp.init(dt);
            //    comp.play();
            //}
            //ImGui::SameLine();
            //if (ImGui::Button("Resume"))
            //{
            //    cmp.resume();
            //}
            //ImGui::SameLine();
            //if (ImGui::Button("Pause"))
            //{
            //    cmp.pause();
            //}
            //ImGui::SameLine();
            //if (ImGui::Button("Stop"))
            //{
            //    cmp.stop();
            //}
            //ImGui::SameLine();
            //if (ImGui::Button("Replay"))
            //{
            //    cmp.stop();
            //    cmp.play();
            //}
//
            //DrawVec3Control("Position", cmp.data.position, 0.0f, 100.0f);
            //DrawVec3Control("Velocity", cmp.data.velocity, 0.0f, 100.0f);
        }
#endif

        ImGui::Separator();
        modules.renderDetailsPanelModules(&ent, bReturn);
    }
    ImGui::End();
    return bReturn;
}
#endif