#pragma once
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
            funcs.emplace_back([&](int button, int action){
                if (button == key && action == event)
                {
                    func();
                }
            });
        }

        void callEvents(int& button, int& action)
        {
            for (auto& a : funcs)
            {
                a(button, action);
            }
        }

    private:
        std::vector<std::function<void(int&, int&)>> funcs = {};

    };
}

inline UVK::Input input;