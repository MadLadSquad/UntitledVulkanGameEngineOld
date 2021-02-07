#pragma once
// InputSystem.hpp
// Last update 2/7/2021 by Madman10K
#include <Core.hpp>
#include "Keys.hpp"

namespace UVK
{
    class Input
    {
    public:
        Input() = default;

        void inputKeyEvent(int key, int event, std::function<void(void)>func)
        {
            funcsKey.emplace_back([&](int button, int action)
            {
                if (button == key && action == event)
                {
                    func();
                }
            });
        }

        void inputMouseMove(std::function<void(void)>func)
        {
            funcsMouseMove.emplace_back(func);
        }

        void inputMouseButton(int key, int event, std::function<void(void)>func)
        {
            funcsMouseKey.emplace_back([&](int button, int action)
            {
                if (button == key && action == event)
                {
                    func();
                }
            });
        }

        void inputScrollWheel(std::function<void(void)> func)
        {
            funcsScrollWheel.emplace_back(func);
        }

        void callKeyEvents(int& button, int& action)
        {
            for (auto& a : funcsKey)
            {
                a(button, action);
            }
        }

        void callMouseMoveEvents()
        {
            for (auto& a : funcsMouseMove)
            {
                a();
            }
        }

        void callMouseClickEvents(int& button, int& action)
        {
            for (auto& a : funcsMouseKey)
            {
                a(button, action);
            }
        }

        void callScrollWheelEvents()
        {
            for (auto& a : funcsScrollWheel)
            {
                a();
            }
        }
    private:
        std::vector<std::function<void(int&, int&)>> funcsKey = {};
        std::vector<std::function<void(void)>> funcsMouseMove = {};
        std::vector<std::function<void(int&, int&)>> funcsMouseKey = {};
        std::vector<std::function<void(void)>> funcsScrollWheel = {};
    };
}

inline UVK::Input input;