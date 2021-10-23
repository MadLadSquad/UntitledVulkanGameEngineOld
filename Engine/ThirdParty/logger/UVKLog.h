#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <functional>
#include <sstream>

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

struct CommandType
{
    std::string cmd; // the name of the command;
    std::string cmdHint; // shown in the help message
    std::function<void(void)> func; // executes the command instructions
};

class Timer
{
public:
    void startRecording();
    void stopRecording();

    ~Timer();

    [[nodiscard]] double getDuration() const;
private:
    double duration = 0;

    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

class UVKLog
{
public:
    UVKLog();
    ~UVKLog();

    void setCrashOnError(bool bErr);
    void setLogFileLocation(const char* file);

    // A general logging function that is useful for when you want to print to the console and to a file
    template<typename... args>
    void generalLog(const char* message, LogType messageType, args&&... argv)
    {
        consoleLog(message, messageType, argv...);
        fileLog(message, messageType, argv...);
    }

    // Simple console log function that acts similarly to printf but doesn't require formatting
    template<typename... args>
    void consoleLog(const char* message, LogType messageType, args&&... argv)
    {
        bool bError = false;
        std::stringstream ss;

        switch (messageType)
        {
        case UVK_LOG_TYPE_WARNING:
            ss << LogColYellow << "[" << getCurrentTime() << "] Warning: " << message;
            break;
        case UVK_LOG_TYPE_ERROR:
            ss << LogColRed << "[" << getCurrentTime() << "] Error: ";

            if (bErroring)
            {
                bError = true;
            }
            break;
        case UVK_LOG_TYPE_NOTE:
            ss << LogColBlue << "[" << getCurrentTime() << "] Note: ";
            break;
        case UVK_LOG_TYPE_SUCCESS:
            ss << LogColGreen << "[" << getCurrentTime() << "] Success: ";
            break;
        case UVK_LOG_TYPE_MESSAGE:
            ss << LogColWhite << "[" << getCurrentTime() << "] Message: ";
            break;
        }
        ss << message;
        (ss << ... << argv);

        std::cout << ss.str() << LogColNull << std::endl;

        std::string log = ss.str();
        log.erase(0, 5);
        messageLog.emplace_back(std::make_pair(log, messageType));

        if (bError)
        {
            std::cin.get();
            throw std::runtime_error(" ");
        }
    }

    // Simple file logging function
    template<typename... args>
    void fileLog(const char* message, LogType messageType, args&&... argv)
    {
        bool bError = false;
        std::stringstream ss;
        ss << "[" << getCurrentTime();
        switch (messageType)
        {
            case UVK_LOG_TYPE_WARNING:
                ss << "] Warning: " << message;
                break;
            case UVK_LOG_TYPE_ERROR:
                ss << "] Error: ";

                if (bErroring)
                {
                    bError = true;
                }
                break;
            case UVK_LOG_TYPE_NOTE:
                ss << "] Note: ";
                break;
            case UVK_LOG_TYPE_SUCCESS:
                ss << "] Success: ";
                break;
            case UVK_LOG_TYPE_MESSAGE:
                ss << "] Message: ";
                break;
        }
        ss << message;
        (ss << ... << argv);
        ss << LogColNull;

        fileout << ss.str() << std::endl;
        messageLog.emplace_back(std::make_pair(ss.str(), messageType));

        if (bError)
        {
            std::cin.get();
            throw std::runtime_error(" ");
        }
    }
private:
    friend class UVKLogImGui;


    static std::string getCurrentTime();
    void shutdownFileStream();

    std::ofstream fileout;
    bool bErroring = false;
    std::vector<std::pair<std::string, LogType>> messageLog;

    std::vector<CommandType> commands;
};

// Yes I know global variables are bad but singletons are worse so I will not even bother
inline UVKLog logger;