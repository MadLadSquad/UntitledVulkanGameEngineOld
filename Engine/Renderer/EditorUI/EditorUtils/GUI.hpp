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