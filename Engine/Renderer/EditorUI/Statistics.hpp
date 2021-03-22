// Statistics.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <imgui.h>
#include <../imguiex/implot/implot.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace Statistics
{
    // This is from the implot demo
    struct RollingBuffer {
        float Span;
        ImVector<ImVec2> Data;
        RollingBuffer() {
            Span = 10.0f;
            Data.reserve(300);
        }
        void AddPoint(float x, float y) {
            float xmod = fmodf(x, Span);
            if (!Data.empty() && xmod < Data.back().x)
                Data.shrink(0);
            Data.push_back(ImVec2(xmod, y));
        }
    };

    // Displays statistics
    static void display()
    {
        ImGui::Begin("Statistics");

        ImGui::Text("Performance: %.3f ms(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        
        // I literally copy pasted this from the implot_demp.cpp because I do not understand anything because no docs
        ImGui::Text("Framerate Charts:");
        static RollingBuffer rdata1, rdata2, rdata3, rdata4;
        static float t = 0;
        t += ImGui::GetIO().DeltaTime;
        rdata1.AddPoint(t, ImGui::GetIO().Framerate);
        rdata2.AddPoint(t, ImGui::GetIO().Framerate);
        rdata3.AddPoint(t, 1000.0f / ImGui::GetIO().Framerate);
        rdata4.AddPoint(t, 1000.0f / ImGui::GetIO().Framerate);

        // NEVER MAKE THIS HIGHER THAN 1 SECOND. PERFORMANCE IMPACT CAN BE AS LARGE AS 97% LOWER FRAME TIMINGS
        rdata1.Span = 1.0f;
        rdata2.Span = 1.0f;
        rdata3.Span = 1.0f;
        rdata4.Span = 1.0f;

        static ImPlotAxisFlags rt_axis = ImPlotAxisFlags_NoTickLabels;
        
        ImPlot::SetNextPlotLimitsX(0, 1.0f, ImGuiCond_Always);
        ImPlot::SetNextPlotLimitsY(0, 1);
        
        if (ImPlot::BeginPlot("##Rolling", NULL, NULL, ImVec2(-1, 150), 0, rt_axis, rt_axis)) {
            ImPlot::PlotLine("##Framerate", &rdata2.Data[0].x, &rdata2.Data[0].y, rdata2.Data.size(), 0, 2 * sizeof(float));
            ImPlot::EndPlot();
        }
        
        ImGui::Text("Frame Timing Charts:");

        ImPlot::SetNextPlotLimitsX(0, 1.0f, ImGuiCond_Always);
        ImPlot::SetNextPlotLimitsY(0, 1);
        if (ImPlot::BeginPlot("##Rollingaaaaa", NULL, NULL, ImVec2(-1, 150), 0, rt_axis, rt_axis)) {
            ImPlot::PlotLine("##Frametime", &rdata4.Data[0].x, &rdata4.Data[0].y, rdata4.Data.size(), 0, 2 * sizeof(float));
            ImPlot::EndPlot();
        }
        ImGui::End();
    }
}