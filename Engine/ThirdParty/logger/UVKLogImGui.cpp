#include "UVKLogImGui.h"
#ifndef PRODUCTION
#ifdef UVK_LOG_IMGUI
#include "cpp/imgui_stdlib.h"
void UVKLogImGui::setLogColour(ImVec4 colour, LogType type)
{
    switch (type)
    {
    case UVK_LOG_TYPE_WARNING:
        warning = colour;
        return;
    case UVK_LOG_TYPE_ERROR:
        error = colour;
        return;
    case UVK_LOG_TYPE_NOTE:
        note = colour;
        return;
    case UVK_LOG_TYPE_SUCCESS:
        success = colour;
        return;
    case UVK_LOG_TYPE_MESSAGE:
        message = colour;
        return;
    }
}

void UVKLogImGui::display()
{
    for (auto& a : logger.messageLog)
    {
        ImVec4 colour;
        switch (a.second)
        {
        case UVK_LOG_TYPE_WARNING:
            colour = warning;
            break;
        case UVK_LOG_TYPE_ERROR:
            colour = error;
            break;
        case UVK_LOG_TYPE_NOTE:
            colour = note;
            break;
        case UVK_LOG_TYPE_SUCCESS:
            colour = success;
            break;
        case UVK_LOG_TYPE_MESSAGE:
            colour = message;
            break;
        }

        ImGui::TextColored(colour, "%s", a.first.c_str());
    }

    static std::string command;
    ImGui::InputTextWithHint("##Input", "Enter any command here", &command);
    ImGui::SameLine();
    if (ImGui::Button("Send##consoleCommand"))
    {
        for (auto& a : logger.commands)
        {
            if (a.cmd == command)
            {
                a.func();
                break;
            }
        }
        command.clear();
    }
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
}

void UVKLogImGui::addToMessageLog(const std::string& msg, LogType type)
{
    logger.messageLog.emplace_back(msg, type);
}

void UVKLogImGui::addCommand(const CommandType& cmd)
{
    logger.commands.emplace_back(cmd);
}

void UVKLogImGui::showHelpMessage()
{
    for (const auto& a : logger.commands)
    {
        addToMessageLog(std::string(a.cmd) + " - " + a.cmdHint, UVK_LOG_TYPE_MESSAGE);
    }
}

void UVKLogImGui::displayFull(bool& bOpen)
{
    ImGui::Begin("Developer Console", &bOpen);
    display();
    ImGui::End();
}
#endif
#endif