// Defines.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
// Defines
#define UVK_API

// This is for MinGW32 because it is retarded
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