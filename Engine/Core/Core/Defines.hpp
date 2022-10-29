#pragma once
#include <any>
#include "Generated/BuildDef.hpp"
#ifdef _WIN32
    #ifdef UVK_LIB_COMPILE
        #define UVK_PUBLIC_API __declspec(dllexport)
    #else
        #define UVK_PUBLIC_API __declspec(dllimport)
    #endif
#else
    #define UVK_PUBLIC_API
#endif
#include <UVKLog.h>
using namespace UVKLog;

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
    #error "Compiling against MinGW is not supported!"
#endif

#ifdef PRODUCTION
    #define UVK_START(x) std::ios_base::sync_with_stdio(!(x)); \
    Logger::setLogOperation(UVKLog::UVK_LOG_OPERATION_FILE_AND_TERMINAL); \
    Logger::setCurrentLogFile("../Generated/run.log"); \
    Logger::setCrashOnError(true); \
    UVK::Utility::removeConsole()
#else
    #define UVK_START(x) std::ios_base::sync_with_stdio(!(x)); \
    Logger::setLogOperation(UVKLog::UVK_LOG_OPERATION_FILE_AND_TERMINAL); \
    Logger::setCurrentLogFile("../Generated/run.log")
#endif


#ifdef PRODUCTION
    // TODO: Make it so that it refers to the archive!
    #define UVK_CONTENT_PATH "../Content/"
#else
    #define UVK_CONTENT_PATH "../Content/"
#endif
#define UVK_CONFIG_ENGINE_PATH "../Config/Engine/"
#define UVK_CONFIG_SETTINGS_PATH "../Config/Settings/"
#define UVK_CONFIG_PRJ_PATH "../"

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

#define VK_MAX_CONCURRENT_IMAGE_DRAW 2

#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// The max number of objects allowed
#define VK_MAX_OBJECTS 100000

// The max number of point lights allowed
#define VK_MAX_DYNAMIC_POINT_LIGHTS 4096

//#define GLEW_STATIC