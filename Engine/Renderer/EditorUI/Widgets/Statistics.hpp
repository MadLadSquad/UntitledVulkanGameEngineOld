// Statistics.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <imgui.h>
#include <Engine/ThirdParty/imguiex/implot/implot.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

#ifndef PRODUCTION
/**
 * @brief Displays a statistics widget used for showcasing framerates, frametimes and load times among other things
 */
namespace Statistics
{
    // This is from the implot demo
    struct RollingBuffer
    {
        float Span;
        ImVector<ImVec2> Data;
        RollingBuffer();
        void AddPoint(float x, float y);
    };

    void display(double* data, bool& bShow);
}
#endif