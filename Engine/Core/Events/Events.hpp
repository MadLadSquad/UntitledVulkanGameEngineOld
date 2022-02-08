// Events.hpp
// Last update 7/2/2022 by Madman10K
#pragma once

namespace UVK
{
    class ScriptableObject;
    /**
     * @brief A class to handle calling of events of scriptable objects
     */
    class UVK_PUBLIC_API Events
    {
    public:
        Events() = delete;
        Events(const Events&) = delete;
        void operator=(Events const&) = delete;
    private:
        friend class Level;
        friend class GLPipeline;
        friend class VulkanRenderer;
        friend class Actor;

        static void callTick(float deltaTime);
        static void callBegin();
        static void callEnd();

        static void clear();
    };
}