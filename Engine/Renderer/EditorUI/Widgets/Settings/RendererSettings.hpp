// RendererSettings.cpp
// Last update 18/2/2022 by Madman10K
#pragma once

namespace UVK
{
    class Editor;
    class RendererSettingsWidget
    {
    private:
        static void display(bool& bReturn, bool& bOpen, Editor& editor);
        friend class SettingsWidgets;
    };
}