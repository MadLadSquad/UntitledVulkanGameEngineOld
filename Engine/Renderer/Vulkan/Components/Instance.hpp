// Instance.hpp
// Last update 26/02/2022 by Madman10K
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