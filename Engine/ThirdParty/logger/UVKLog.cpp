#include "UVKLog.h"
#include <ctime>
#include "UVKLogImGui.h"

#if _MSC_VER && !__INTEL_COMPILER
    #define _CRT_SECURE_NO_WARNINGS
#endif

void Timer::startRecording()
{
    start = std::chrono::high_resolution_clock::now();
}

void Timer::stopRecording()
{
    auto endTime = std::chrono::high_resolution_clock::now();
    auto st = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

    auto dt = end - st;

    duration = (double)dt * 0.001;
}

Timer::~Timer()
{
    stopRecording();
}

double Timer::getDuration() const
{
    return duration;
}

UVKLog::~UVKLog()
{
    shutdownFileStream();
}

void UVKLog::setCrashOnError(bool bErr)
{
    bErroring = bErr;
}

void UVKLog::setLogFileLocation(const char* file)
{
    fileout = std::ofstream(file);
}

void UVKLog::shutdownFileStream()
{
    fileout.close();
}

std::string UVKLog::getCurrentTime()
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string realTime = std::ctime(&now);
    realTime.erase(24);

    return realTime;
}

UVKLog::UVKLog()
{
#ifdef UVK_LOG_IMGUI
    const CommandType clear =
    {
        .cmd = "clear",
        .cmdHint = "Clears the scroll buffer",
        .func = [&](){ messageLog.clear(); },
    };

    const CommandType help
    {
        .cmd = "help",
        .cmdHint = "Sends a help message",
        .func = UVKLogImGui::showHelpMessage
    };

    commands.emplace_back(clear);
    commands.emplace_back(help);
#endif
}
