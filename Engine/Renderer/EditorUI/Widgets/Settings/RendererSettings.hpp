#pragma once

namespace UVK
{
    class Editor;
    class RendererSettingsWidget
    {
    private:
        static void display(bool& bReturn, bool& bOpen, Editor& editor) noexcept;
        friend class SettingsWidgets;
    };
}