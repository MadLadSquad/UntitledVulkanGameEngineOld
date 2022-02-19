// Resources.hpp
// Last update 18/2/2022 by Madman10K
#pragma once
#include <Core/Defines.hpp>

namespace UVK
{
    class Editor;
    class EditorResources
    {
    private:
        static void loadConfigs(Editor& editor);

#ifndef __MINGW32__
        static void loadResources(Editor& editor, std_filesystem::path& pt);
#else
        static void loadResources(Editor& editor);
#endif
        friend class Editor;
    };
}