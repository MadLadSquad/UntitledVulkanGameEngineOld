// Defines.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
// Defines
#define UVK_API

#ifndef __MINGW32__
    #if __has_include(<filesystem>)
        #include <filesystem>
        #define std_filesystem std::filesystem
    #else
        #include <experimental/filesystem>
        #define std_filesystem std::experimental::filesystem
    #endif
#else

#endif