#pragma once
#include <Core/Defines.hpp>

namespace UVK
{
    class Editor;
    class EditorResources
    {
    private:
        static void loadConfigs(Editor& editor) noexcept;

#ifndef __MINGW32__
        static void loadResources(Editor& editor, std_filesystem::path& pt) noexcept;
#else
        static void loadResources(Editor& editor) noexcept;
#endif
        friend class Editor;
    };
}