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

        static void callTick(float deltaTime) noexcept;
        static void callBegin() noexcept;
        static void callEnd() noexcept;

        static void clear() noexcept;
    };
}