#pragma once

namespace UVK
{
    class Editor;
    class EditorUtilSettings
    {
    private:
        static void loadImGuiSettings(Editor& editor, const char* colTheme) noexcept;
        static void setImGuiSettings(Editor& editor) noexcept;
        static void finishImGuiRender(Editor& editor) noexcept;
        friend class Editor;
    };
}