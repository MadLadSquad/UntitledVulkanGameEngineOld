#pragma once
#include "UVKLog.h"
#define UVK_LOG_IMGUI
#ifdef UVK_LOG_IMGUI
#if __has_include(<imgui.h>)
#include "imgui.h"

class UVKLogImGui
{
public:
    void displayFull(bool& bOpen);
    void display();

    static void addToMessageLog(const std::string& msg, LogType type);
    static void addCommand(const CommandType& cmd);

    void setLogColour(ImVec4 colour, LogType type);
private:
    friend class UVKLog;

    static void showHelpMessage();

    ImVec4 success = { 0.0f, 1.0f, 0.0f, 1.0f };
    ImVec4 warning = { 1.0f, 1.0f, 0.0f, 1.0f };
    ImVec4 error = { 1.0f, 0.0f, 0.0f, 1.0f };
    ImVec4 note = { 0.0f, 0.0f, 1.0f, 1.0f };
    ImVec4 message = { 1.0f, 1.0f, 1.0f, 1.0f };
};
#else
#error Dear ImGui is not in the include path!. Consider adding it so that "#include <imgui.h>" is a valid line
#endif
#endif