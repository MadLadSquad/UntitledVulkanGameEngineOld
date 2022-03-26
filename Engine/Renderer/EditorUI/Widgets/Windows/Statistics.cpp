#include "Statistics.hpp"

#ifndef PRODUCTION
Statistics::RollingBuffer::RollingBuffer() noexcept
{
    Span = 1.0f;
    Data.reserve(200);
}

void Statistics::RollingBuffer::AddPoint(float x, float y) noexcept
{
    float xmod = fmodf(x, Span);
    if (!Data.empty() && xmod < Data.back().x)
        Data.shrink(0);
    Data.push_back(ImVec2(xmod, y));
}

void Statistics::display(double* data, bool& bShow) noexcept
{
    ImGui::Begin("Statistics", &bShow);

    ImGui::Text("Performance: %.3f ms(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    static int frame = 0;
    frame++;
    // I literally copy pasted this from the implot_demp.cpp because I do not understand anything because no docs
    ImGui::Text("Framerate Charts:");
    static RollingBuffer rdata, rdata1;
    static float t = 0;
    t += ImGui::GetIO().DeltaTime;
    if (frame > (int)(ImGui::GetIO().Framerate / 60))
    {
        rdata.AddPoint(t, ImGui::GetIO().Framerate);
        rdata1.AddPoint(t, 1000.0f / ImGui::GetIO().Framerate);
    }

    // NEVER MAKE THIS HIGHER THAN 1 SECOND. PERFORMANCE IMPACT CAN BE AS LARGE AS 97% LOWER FRAME TIMINGS
    rdata.Span = 0.5f;
    rdata1.Span = 0.5f;

    static ImPlotAxisFlags rt_axis = ImPlotAxisFlags_NoTickLabels;

    //ImPlot::SetNextPlotLimitsX(0, 0.5f, ImGuiCond_Always);
    //ImPlot::SetNextPlotLimitsY(0, 1);
    if (ImPlot::BeginPlot("##Rolling", ImVec2(-1, 150), 0))
    //if (ImPlot::BeginPlot("##Rolling", nullptr, nullptr, ImVec2(-1, 150), 0, rt_axis, rt_axis))
    {
        ImPlot::SetupAxis(ImAxis_X1, nullptr, rt_axis);
        ImPlot::SetupAxis(ImAxis_Y1, nullptr, rt_axis);
        ImPlot::SetupAxisLimits(ImAxis_X1, 0, 0.5f, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);

        ImPlot::PlotLine("##Framerate", &rdata.Data[0].x, &rdata.Data[0].y, rdata.Data.size(), 0, 2 * sizeof(float));
        ImPlot::EndPlot();
    }

    ImGui::Text("Frame Timing Charts:");

    //ImPlot::SetNextPlotLimitsX(0, 0.5f, ImGuiCond_Always);
    //ImPlot::SetNextPlotLimitsY(0, 1);

    if (ImPlot::BeginPlot("##Rollingaaaaa", ImVec2(-1, 150), 0))
    //if (ImPlot::BeginPlot("##Rollingaaaaa", nullptr, nullptr, ImVec2(-1, 150), 0, rt_axis, rt_axis))
    {
        ImPlot::SetupAxis(ImAxis_X1, nullptr, rt_axis);
        ImPlot::SetupAxis(ImAxis_Y1, nullptr, rt_axis);
        ImPlot::SetupAxisLimits(ImAxis_X1, 0, 0.5f, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);

        ImPlot::PlotLine("##Frametime", &rdata1.Data[0].x, &rdata1.Data[0].y, rdata1.Data.size(), 0, 2 * sizeof(float));
        ImPlot::EndPlot();
    }

    ImGui::Text("Loading time (in ms): ");


    //ImPlot::SetNextPlotLimits(0,1,0,1,ImGuiCond_Always);

    //if (ImPlot::BeginPlot("##Pie1", nullptr, nullptr, ImVec2(350,350), ImPlotFlags_Equal | ImPlotFlags_NoMousePos, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations))
    if (ImPlot::BeginPlot("##Pie1", ImVec2(350, 350), ImPlotFlags_Equal | ImPlotFlags_NoMouseText))
    {
        static const char* labels[] = { "Start", "Last Level"};
        double dt[] = { data[0], data[1] };

        ImPlot::SetupAxis(ImAxis_X1, nullptr, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxis(ImAxis_Y1, nullptr, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxesLimits(0, 1, 0, 1, ImPlotCond_Always);

        ImPlot::SetupLegend(ImPlotLocation_North | ImPlotLocation_West, ImPlotLegendFlags_Horizontal);
        ImPlot::PlotPieChart(labels, dt, 2, 0.5, 0.5, 0.4, true, "%.3f");
        ImPlot::EndPlot();
    }

    ImGui::End();
}
#endif