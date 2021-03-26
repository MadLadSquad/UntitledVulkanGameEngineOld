#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <ios>
#include <chrono>
#include <ctime>
#include <functional>



enum LogType
{
    UVK_LOG_TYPE_WARNING,
    UVK_LOG_TYPE_ERROR,
    UVK_LOG_TYPE_NOTE,
    UVK_LOG_TYPE_SUCCESS,
    UVK_LOG_TYPE_MESSAGE
};

class UVKLog
{
public:
    UVKLog() = default;

    void setLogFileLocation(const char* file)
    {
        fileout = std::ofstream(file);
    }

    const char* getLogFileLocation()
    {
        //return fileout.getloc().global().name();
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
            std::cout << "\033[0m" << std::endl;

            fileout << "[" << getCurrentTime() << "] Warning: " << message;
            (fileout << ... << argv);
            fileout << std::endl;
            
            break;
        case UVK_LOG_TYPE_ERROR:
            std::cout << LogColRed << "[" << getCurrentTime() << "] Error: " << message;
            (std::cout << ... << argv);
            std::cout << "\033[0m" << std::endl;

            fileout << "[" << getCurrentTime() << "] Error: " << message;
            (fileout << ... << argv);
            fileout << std::endl;
            break;
        case UVK_LOG_TYPE_NOTE:
            std::cout << LogColBlue << "[" << getCurrentTime() << "] Note: " << message;
            (std::cout << ... << argv);
            std::cout << "\033[0m" << std::endl;

            fileout << "[" << getCurrentTime() << "] Note: " << message;
            (fileout << ... << argv);
            fileout << std::endl;
            break;
        case UVK_LOG_TYPE_SUCCESS:
            std::cout << LogColGreen << "[" << getCurrentTime() << "] Success: " << message;
            (std::cout << ... << argv);
            std::cout << "\033[0m" << std::endl;

            fileout << "[" << getCurrentTime() << "] Success: " << message;
            (fileout << ... << argv);
            fileout << std::endl;
            break;
        case UVK_LOG_TYPE_MESSAGE:
            std::cout << LogColWhite << "[" << getCurrentTime() << "] Message: " << message;
            (std::cout << ... << argv);
            std::cout << "\033[0m" << std::endl;

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
            std::cout << "\033[0m" << std::endl;

            break;
        case UVK_LOG_TYPE_ERROR:
            std::cout << LogColRed << "[" << getCurrentTime() << "] Error: " << message;
            (std::cout << ... << argv);
            std::cout << "\033[0m" << std::endl;

            break;
        case UVK_LOG_TYPE_NOTE:
            std::cout << LogColBlue << "[" << getCurrentTime() << "] Note: " << message;
            (std::cout << ... << argv);
            std::cout << "\033[0m" << std::endl;

            break;
        case UVK_LOG_TYPE_SUCCESS:
            std::cout << LogColGreen << "[" << getCurrentTime() << "] Success: " << message;
            (std::cout << ... << argv);
            std::cout << "\033[0m" << std::endl;

            break;
        case UVK_LOG_TYPE_MESSAGE:
            std::cout << LogColWhite << "[" << getCurrentTime() << "] Message: " << message;
            (std::cout << ... << argv);
            std::cout << "\033[0m" << std::endl;

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
    std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        // This temporary is required
        std::string realTime = std::ctime(&now);

        // You may ask why do I even do this and the answer is we want to remove the \n that the ctime function appends
        // to the end of the string and we also don't want to add a space because I don't like unnecessary spaces so
        // here we are removing the 25th character of the string and replacing it with null
        realTime[24] = NULL;

        return realTime;
    }

    std::ofstream fileout;

    // Don't ask me why
    static constexpr char* LogColGreen = "\x1B[32m";
    static constexpr char* LogColYellow = "\x1B[33m";
    static constexpr char* LogColRed = "\x1B[31m";
    static constexpr char* LogColWhite = "\x1B[37m";
    static constexpr char* LogColBlue = "\x1B[34m";
};

// Yes I know global variables are bad but singletons are worse so I will not even bother
inline UVKLog logger;

