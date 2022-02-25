// Instance.hpp
// Last update 21/12/2021 by Madman10K
#pragma once

namespace UVK
{

    class VKInstance
    {
    public:
        VKInstance() = default;
        void create();
        void destroy();
        VkInstance& data();
    private:
        static bool checkInstanceExtensionsSupport(const char** extensions, uint32_t count);

        VkInstance instance;
    };
}