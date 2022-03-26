#pragma once
#include <Core.hpp>
#ifndef PRODUCTION
#include <imgui.h>
#include <Engine/ThirdParty/imguiex/implot/implot.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

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
        RollingBuffer() noexcept;
        void AddPoint(float x, float y) noexcept;
    };

    void display(double* data, bool& bShow) noexcept;
}
#endif