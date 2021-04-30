#pragma once
#include <csignal>
#ifdef __linux__
    #include <unistd.h>
    #include <sys/wait.h>
    #include <fcntl.h>
    #include <pty.h>
    #include <poll.h>
#else
    #ifdef __APPLE__
        #include <unistd.h>
        #include <sys/wait.h>
        #include <fcntl.h>
        #include <util.h>
        #include <poll.h>
    #else

    #endif
#endif

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

namespace ImTTY
{
    struct ImTTYData
    {

    };
    class Term
    {
    public:
        void CreateContext()
        {
#ifndef _WIN32

            ws.ws_col = 1360;
            ws.ws_row = 768;

            pid = forkpty(&fd, nullptr, nullptr, &ws);
            if(!pid)
            {
                putenv((char*)"TERM=xterm");
                execl(std::getenv("SHELL"), std::getenv("SHELL"), "-l", "-i", nullptr);
            }

            fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
#else

#endif
        }

        void KillTTY(int signal) const
        {
#ifndef _WIN32
            kill(pid, signal);
#else

#endif
        }

        void DestroyContext()
        {
#ifndef _WIN32
            KillTTY(SIGHUP);

            kill(pid, SIGTERM);
            close(fd);
            waitpid(pid, nullptr, 0);
#else

#endif
        }

        void ResizeTTY(int x, int y)
        {
#ifndef _WIN32
            ws.ws_col = x;
            ws.ws_row = y;
            ioctl(fd, TIOCSWINSZ, &ws);
#else

#endif
        }

        std::pair<std::string, int> GetData()
        {
            char buffer[4096];
            std::pair<std::string, int> result;
#ifndef _WIN32
            result.second = read(fd, buffer, sizeof(buffer));
#else

#endif
            if(result.second > 0)
                result.first.assign(buffer, buffer+result.second);

            return result;
        }

        void SendTTY(std::string& cmd)
        {
#if __linux__ || __APPLE__
            write(fd, cmd.data(), cmd.size());
#else

#endif
        }

        std::string DrawContents(std::string& command, bool& bFinalStr)
        {
            if (!command.empty() && bFinalStr)
            {
                SendTTY(command);

                auto input = GetData();

                if (input.second == -1)
                {
                    logger.consoleLog("Error with getting data from tty", UVK_LOG_TYPE_ERROR);
                }

                std::cout << input.first << std::flush;

                command.clear();

                return input.first;
            }

            bFinalStr = false;

            return " ";
        }
    private:
        int fd = 0;
        int master = 0;
        int pid = 0;
        int child = 0;

        winsize ws{};
    };

    inline Term Terminal;
}
