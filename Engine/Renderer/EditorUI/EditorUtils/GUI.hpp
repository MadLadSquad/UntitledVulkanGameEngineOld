#pragma once

namespace UVK
{
    class Editor;
    /**
     * @brief Simplifies some of the GUI rendering work done by the editor like rendering the menubar and activating editor keybind actions
     */
    class EditorGUIUtils
    {
    private:
        static void renderMenubar(Editor& editor) noexcept;
        static void switchKeybinds(Editor& editor) noexcept;
        friend class Editor;
    };
}