// GUI.hpp
// Last update 18/2/2022 by Madman10K
#pragma once

namespace UVK
{
    class Editor;
    class EditorGUIUtils
    {
    private:
        static void renderMenubar(Editor& editor) noexcept;
        static void switchKeybinds(Editor& editor) noexcept;
        friend class Editor;
    };
}