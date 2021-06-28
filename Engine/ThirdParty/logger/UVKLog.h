#pragma once
#if _MSC_VER && !__INTEL_COMPILER
    #define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <fstream>
#include <ostream>
#include <ios>
#include <chrono>
#include <ctime>
#include <functional>

#define LogColGreen "\x1B[32m"
#define LogColYellow "\x1B[33m"
#define LogColRed "\x1B[31m"
#define LogColWhite "\x1B[37m"
#define LogColBlue "\x1B[34m"
#define LogColNull "\033[0m"

enum LogType
{
    UVK_LOG_TYPE_WARNING,
    UVK_LOG_TYPE_ERROR,
    UVK_LOG_TYPE_NOTE,
    UVK_LOG_TYPE_SUCCESS,
    UVK_LOG_TYPE_MESSAGE
};

class Timer
{
public:
    void startRecording()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    void stopRecording()
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto st = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

        auto dt = end - st;

        duration = (double)dt * 0.001;
    }

    ~Timer()
    {
        stopRecording();
    }

    [[nodiscard]] double getDuration() const
    {
        return duration;
    }
private:
    double duration = 0;

    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

class UVKLog
{
public:
    UVKLog() = default;

    void setCrashOnError(bool bErr)
    {
        bErroring = bErr;
    }

    void setLogFileLocation(const char* file)
    {
        fileout = std::ofstream(file);
    }

    // A general logging function that is useful for when you want to print to the console and to a file
    template<typename... args>
    void generalLog(const char* message, LogType messageType, args&&... argv)
    {
        switch (messageType)
        {
        case UVK_LOG_TYPE_WARNING:
            std::cout << LogColYellow << "[" << getCurrentTime() << "] Warning: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            fileout << "[" << getCurrentTime() << "] Warning: " << message;
            (fileout << ... << argv);
            fileout << std::endl;
            
            break;
        case UVK_LOG_TYPE_ERROR:
            std::cout << LogColRed << "[" << getCurrentTime() << "] Error: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            fileout << "[" << getCurrentTime() << "] Error: " << message;
            (fileout << ... << argv);
            fileout << std::endl;

            if (bErroring)
            {
                std::cin.get();
                throw std::runtime_error(" ");
            }
            break;
        case UVK_LOG_TYPE_NOTE:
            std::cout << LogColBlue << "[" << getCurrentTime() << "] Note: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            fileout << "[" << getCurrentTime() << "] Note: " << message;
            (fileout << ... << argv);
            fileout << std::endl;
            break;
        case UVK_LOG_TYPE_SUCCESS:
            std::cout << LogColGreen << "[" << getCurrentTime() << "] Success: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            fileout << "[" << getCurrentTime() << "] Success: " << message;
            (fileout << ... << argv);
            fileout << std::endl;
            break;
        case UVK_LOG_TYPE_MESSAGE:
            std::cout << LogColWhite << "[" << getCurrentTime() << "] Message: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            fileout << "[" << getCurrentTime() << "] Message: " << message;
            (fileout << ... << argv);
            fileout << std::endl;
            break;
        }
    }

    // Simple console log function that acts similarly to printf but doesn't require formatting
    template<typename... args>
    void consoleLog(const char* message, LogType messageType, args&&... argv)
    {
        switch (messageType)
        {
        case UVK_LOG_TYPE_WARNING:
            std::cout << LogColYellow << "[" << getCurrentTime() << "] Warning: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            break;
        case UVK_LOG_TYPE_ERROR:
            std::cout << LogColRed << "[" << getCurrentTime() << "] Error: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            if (bErroring)
            {
                std::cin.get();
                throw std::runtime_error(" ");
            }
            break;
        case UVK_LOG_TYPE_NOTE:
            std::cout << LogColBlue << "[" << getCurrentTime() << "] Note: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            break;
        case UVK_LOG_TYPE_SUCCESS:
            std::cout << LogColGreen << "[" << getCurrentTime() << "] Success: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            break;
        case UVK_LOG_TYPE_MESSAGE:
            std::cout << LogColWhite << "[" << getCurrentTime() << "] Message: " << message;
            (std::cout << ... << argv);
            std::cout << LogColNull << std::endl;

            break;
        }
    }

    // Simple file logging function
    template<typename... args>
    void fileLog(const char* message, LogType messageType, args&&... argv)
    {
        switch (messageType)
        {
        case UVK_LOG_TYPE_WARNING:
            fileout << "[" << getCurrentTime() << "] Warning: " << message;
            (fileout << ... << argv);
            fileout << std::endl;

            break;
        case UVK_LOG_TYPE_ERROR:
            fileout << "[" << getCurrentTime() << "] Error: " << message;
            (fileout << ... << argv);
            fileout << std::endl;

            if (bErroring)
            {
                std::cin.get();
                throw std::runtime_error("[" + getCurrentTime() + "] Error: " + message);
            }
            break;
        case UVK_LOG_TYPE_NOTE:
            fileout << "[" << getCurrentTime() << "] Note: " << message;
            (fileout << ... << argv);
            fileout << std::endl;

            break;
        case UVK_LOG_TYPE_SUCCESS:
            fileout << "[" << getCurrentTime() << "] Success: " << message;
            (fileout << ... << argv);
            fileout << std::endl;

            break;
        case UVK_LOG_TYPE_MESSAGE:
            fileout << "[" << getCurrentTime() << "] Message: " << message;
            (fileout << ... << argv);
            fileout << std::endl;

            break;
        }
    }

    void shutdownFileStream()
    {
        fileout.close();
    }
private:
    static std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        std::string realTime = std::ctime(&now);
        realTime.erase(24);

        return realTime;
    }

    std::ofstream fileout;
    bool bErroring = false;
};

// Yes I know global variables are bad but singletons are worse so I will not even bother
inline UVKLog logger;