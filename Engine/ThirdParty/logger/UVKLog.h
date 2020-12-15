#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <ios>
#include <chrono>
#include <ctime>
#define LogColGreen  "\x1B[32m"
#define LogColYellow "\x1B[33m"
#define LogColRed "\x1B[31m"
#define LogColWhite  "\x1B[37m"
#define LogColBlue  "\x1B[34m"

typedef std::fstream LogFile;

enum LogType
{
    WARNING,
    ERROR,
    NOTE,
    SUCCESS,
    MESSAGE
};

class UVKLog
{
public:
    template<typename T>
    void ConsoleLogComplex(const char* message, LogType type, std::initializer_list<T> list)
    {
        auto CurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        switch (type)
        {
            case SUCCESS:
                std::cout << LogColGreen << " " << ctime(&CurrentTime) << " Success: " << message;
                for (auto elem : list)
                {
                    std::cout << " " << elem;
                }
                std::cout << std::endl;
                break;
            case WARNING:
                std::cout << LogColYellow << " " << ctime(&CurrentTime) << " Warning: " << message;
                for (auto elem : list)
                {
                    std::cout << " " << elem;
                }
                std::cout << std::endl;
                break;
            case ERROR:
                std::cout << LogColRed << " " << ctime(&CurrentTime) << " Error: " << message;
                for (auto elem : list)
                {
                    std::cout << " " << elem;
                }
                std::cout << std::endl;
                break;
            case NOTE:
                std::cout << LogColBlue << " " << ctime(&CurrentTime) << " Note: " << message;
                for (auto elem : list)
                {
                    std::cout << " " << elem;
                }
                std::cout << std::endl;
                break;
            case MESSAGE:
                std::cout << LogColWhite << " " << ctime(&CurrentTime) << " Message: " << message;
                for (auto elem : list)
                {
                    std::cout << " " << elem;
                }
                std::cout << std::endl;
                break;
        }
    }

    void ConsoleLog(const char* message, LogType type)
    {
        auto CurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        switch (type)
        {
            case SUCCESS:
                std::cout << LogColGreen << " " << ctime(&CurrentTime) << " Success: " << message << std::endl;
                break;
            case WARNING:
                std::cout << LogColYellow << " " << ctime(&CurrentTime) << " Warning: " << message << std::endl;
                break;
            case ERROR:
                std::cout << LogColRed << " " << ctime(&CurrentTime) << " Error: " << message << std::endl;
                break;
            case NOTE:
                std::cout << LogColBlue << " " << ctime(&CurrentTime) << " Note: " << message << std::endl;
                break;
            case MESSAGE:
                std::cout << LogColWhite << " " << ctime(&CurrentTime) << " Message: " << message << std::endl;
                break;
        }
    }

    void FileLog(const char* message, LogType type)
    {
        auto CurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        switch (type)
        {
            case SUCCESS:
                file << "Success: " << " " << ctime(&CurrentTime) << message << std::endl;
                break;
            case WARNING:
                file << "Warning: " << " " << ctime(&CurrentTime) << message << std::endl;
                break;
            case ERROR:
                file << "Error: " << " " << ctime(&CurrentTime) << message << std::endl;
                break;
            case NOTE:
                file << "Note: " << " " << ctime(&CurrentTime) << message << std::endl;
                break;
            case MESSAGE:
                file << "Message: " << " " << ctime(&CurrentTime) << message << std::endl;
                break;
        }
    }

    template<typename T>
    void FileLogComplex(const char* message, LogType type, std::initializer_list<T> list)
    {
        auto CurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        switch (type)
        {
            case SUCCESS:
                file << "Success: " << " " << ctime(&CurrentTime) << message;
                for (auto elem : list)
                {
                    file << " " << elem;
                }
                file << std::endl;
                break;
            case WARNING:
                file << "Warning: " << " " << ctime(&CurrentTime) << message;
                for (auto elem : list)
                {
                    file << " " << elem;
                }
                file << std::endl;
                break;
            case ERROR:
                file << "Error: " << " " << ctime(&CurrentTime) << message;
                for (auto elem : list)
                {
                    file << " " << elem;
                }
                file << std::endl;
                break;
            case NOTE:
                file << "Note: " << " " << ctime(&CurrentTime) << message;
                for (auto elem : list)
                {
                    file << " " << elem;
                }
                file << std::endl;
                break;
            case MESSAGE:
                file << "Message: " << " " << ctime(&CurrentTime) << message;
                for (auto elem : list)
                {
                    file << " " << elem;
                }
                file << std::endl;
                break;
        }
    }

    void CreateFile(const char* location)
    {
        file.open(location);
    }

    void CloseFile()
    {
        file.close();
    }

private:

    std::ofstream file;
};

static UVKLog Log;
