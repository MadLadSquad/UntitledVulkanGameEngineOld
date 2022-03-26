#pragma once

namespace UVK
{
    class Editor;
    class EditorSettingsWidget
    {
    private:
        static void displayEditorSettingsWidget(bool& bReturn, bool& bOpen, Editor& editor) noexcept;
        friend class SettingsWidgets;
    };
}