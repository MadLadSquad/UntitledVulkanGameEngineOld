#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include <iostream>
#include <utility>
#include <imgui.h>

namespace UVK
{
    /**
     * @brief The editor theme class is used to load theme files to customize the editor
     * @note You can find documentation here: https://github.com/MadLadSquad/UntitledVulkanGameEngine/wiki/Themes
     */
    class UVK_PUBLIC_API EditorTheme
    {
    public:
        EditorTheme() = default;

        inline explicit EditorTheme(UVK::String theme) noexcept
        {
            setTheme(theme);
        }

        static void save(UVK::String filename, UVK::String font, int fontSz) noexcept;
    private:
        friend class EditorUtilSettings;

        void setTheme(UVK::String theme) noexcept;
        void useTheme() noexcept;

        std::pair<UVK::FString, int> getFont() noexcept;
        [[nodiscard]] float getWindowRounding() const noexcept;

        ImVec4 textCol = ImVec4(1.0, 1.0, 1.0, 1.0);

        ImVec4 windowBg = ImVec4(0.1, 0.1, 0.1, 1.0);

        ImVec4 header = ImVec4(0.2, 0.2, 0.2, 1.0);
        ImVec4 headerHovered = ImVec4(0.3, 0.3, 0.3, 1.0);
        ImVec4 headerActive = ImVec4(0.15, 0.15, 0.15, 1.0);

        ImVec4 button = ImVec4(0.2, 0.2, 0.2, 1.0);
        ImVec4 buttonHovered = ImVec4(0.3, 0.3, 0.3, 1.0);
        ImVec4 buttonActive = ImVec4(0.15, 0.15, 0.15, 1.0);

        ImVec4 frame = ImVec4(0.2, 0.2, 0.2, 1.0);
        ImVec4 frameHovered = ImVec4(0.3, 0.3, 0.3, 1.0);
        ImVec4 frameActive = ImVec4(0.15, 0.15, 0.15, 1.0);

        ImVec4 tab = ImVec4(0.15, 0.15, 0.15, 1.0);
        ImVec4 tabHovered = ImVec4(0.4, 0.4, 0.4, 1.0);
        ImVec4 tabActive = ImVec4(0.3, 0.3, 0.3, 1.0);
        ImVec4 tabUnfocused = ImVec4(0.15, 0.15, 0.15, 1.0);
        ImVec4 tabUnfocusedActive = ImVec4(0.2, 0.2, 0.2, 1.0);

        ImVec4 titleBg = ImVec4(0.15, 0.15, 0.15, 1.0);
        ImVec4 titleBgCollapsed = ImVec4(0.95, 0.15, 0.95, 1.0);
        ImVec4 titleBgActive = ImVec4(0.15, 0.15, 0.15, 1.0);

        ImVec4 menubarBG = ImVec4(0.01, 0.01, 0.01, 1.0);
        ImVec4 popupBG = ImVec4(0.1, 0.1, 0.1, 1.0);

        UVK::FString fontLoc;
        int fontSize = 12;
        float windowRounding = 1.0f;
    };
}
#endif