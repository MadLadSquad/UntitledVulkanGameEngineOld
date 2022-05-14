#pragma once
#include <Core/Defines.hpp>

namespace UVK
{
    class Editor;
    // A class to load editor resources
    class EditorResources
    {
    private:
        // This function loads all editor configs
        static void loadConfigs(Editor& editor) noexcept;

#ifndef __MINGW32__
        // This function loads all editor resources, i.e textures, models, fonts, etc.
        static void loadResources(Editor& editor, std_filesystem::path& pt) noexcept;
#else
        static void loadResources(Editor& editor) noexcept;
#endif
        friend class Editor;
    };
}