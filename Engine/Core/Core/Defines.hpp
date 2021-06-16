// Defines.hpp
// Last update 18/5/2021 by Madman10K
#pragma once
#include <any>
#include "Generated/BuildDef.hpp"

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

// If this is not set to true iostream will do syncing with stdio which can slow down read speed by a lot
#define ENABLE_FAST_IO(x) std::ios_base::sync_with_stdio(!x)
