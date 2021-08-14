// Defines.hpp
// Last update 12/8/2021 by Madman10K
#pragma once
#include <any>
#include "Generated/BuildDef.hpp"
#include <logger/UVKLog.h>

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

#ifdef PRODUCTION
    #define ENABLE_FAST_IO(x) std::ios_base::sync_with_stdio(!x); \
    logger.setCrashOnError(true)
#else
    #define ENABLE_FAST_IO(x) std::ios_base::sync_with_stdio(!x)
#endif

#define FS_ICON_AUDIO 0
#define FS_ICON_IMAGE 1
#define FS_ICON_VIDEO 2
#define FS_ICON_FOLDER 3
#define FS_ICON_FONT 4
#define FS_ICON_MODEL 5
#define FS_ICON_UNKNOWN 6
#define FS_ICON_CODE 7

#define FC_GAME_MODE 1
#define FC_GAME_STATE 2
#define FC_PLAYER_STATE 3
#define FC_PLAYER_CONTROLLER 4
#define FC_PAWN 5
#define FC_LEVEL 6
#define FC_SCRIPTABLE_OBJECT 7

#define VK_SHADER_STAGE_VERT 0
#define VK_SHADER_STAGE_FRAG 1

#define VK_UNDEFINED_TO_SUBPASS_LAYOUT 0
#define VK_SUBPASS_TO_PRESENTATION_LAYOUT 1