// Statistics.hpp
// Last update 15/5/2021 by Madman10K
#include "Statistics.hpp"

Statistics::RollingBuffer::RollingBuffer()
{
    Span = 1.0f;
    Data.reserve(30);
}

void Statistics::RollingBuffer::AddPoint(float x, float y)
{
    float xmod = fmodf(x, Span);
    if (!Data.empty() && xmod < Data.back().x)
        Data.shrink(0);
    Data.push_back(ImVec2(xmod, y));
}

void Statistics::display(double* data, bool& bShow)
{
    ImGui::Begin("Statistics", &bShow);

    ImGui::Text("Performance: %.3f ms(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    // I literally copy pasted this from the implot_demp.cpp because I do not understand anything because no docs
    ImGui::Text("Framerate Charts:");
    static RollingBuffer rdata, rdata2;
    static float t = 0;
    t += ImGui::GetIO().DeltaTime;
    rdata.AddPoint(t, ImGui::GetIO().Framerate);
    rdata2.AddPoint(t, 1000.0f / ImGui::GetIO().Framerate);

    // NEVER MAKE THIS HIGHER THAN 1 SECOND. PERFORMANCE IMPACT CAN BE AS LARGE AS 97% LOWER FRAME TIMINGS
    rdata.Span = 0.5f;
    rdata2.Span = 0.5f;

    static ImPlotAxisFlags rt_axis = ImPlotAxisFlags_NoTickLabels;

    ImPlot::SetNextPlotLimitsX(0, 0.5f, ImGuiCond_Always);
    ImPlot::SetNextPlotLimitsY(0, 1);

    if (ImPlot::BeginPlot("##Rolling", nullptr, nullptr, ImVec2(-1, 150), 0, rt_axis, rt_axis))
    {
        ImPlot::PlotLine("##Framerate", &rdata.Data[0].x, &rdata.Data[0].y, rdata.Data.size(), 0, 2 * sizeof(float));
        ImPlot::EndPlot();
    }

    ImGui::Text("Frame Timing Charts:");

    ImPlot::SetNextPlotLimitsX(0, 0.5f, ImGuiCond_Always);
    ImPlot::SetNextPlotLimitsY(0, 1);
    if (ImPlot::BeginPlot("##Rollingaaaaa", nullptr, nullptr, ImVec2(-1, 150), 0, rt_axis, rt_axis))
    {
        ImPlot::PlotLine("##Frametime", &rdata2.Data[0].x, &rdata2.Data[0].y, rdata2.Data.size(), 0, 2 * sizeof(float));
        ImPlot::EndPlot();
    }

    ImGui::Text("Loading time (in ms): ");

    ImPlot::SetNextPlotLimits(0,1,0,1,ImGuiCond_Always);
    if (ImPlot::BeginPlot("##Pie1", nullptr, nullptr, ImVec2(350,350), ImPlotFlags_Equal | ImPlotFlags_NoMousePos, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations))
    {
        static const char* labels[] = { "Start", "Last Level"};
        double dt[] = { data[0], data[1] };

        ImPlot::SetLegendLocation(ImPlotLocation_North | ImPlotLocation_West, ImPlotOrientation_Horizontal);
        ImPlot::PlotPieChart(labels, dt, 2, 0.5, 0.5, 0.4, true, "%.3f");
        ImPlot::EndPlot();
    }

    ImGui::End();
}