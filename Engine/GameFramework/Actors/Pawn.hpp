#pragma once
#include <Core.hpp>
#include <Renderer/Camera/Camera.hpp>
#include <Core/Actor.hpp>

namespace UVK
{
    /**
     * @brief an actor that the player can control
     */
    class UVK_PUBLIC_API Pawn
    {
    public:
        Pawn() = default;

        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        virtual ~Pawn() noexcept;
        Camera camera;

        FString name;
        int64_t id{};
        FString devName;

        Actor actor{};

        template<typename T>
        inline static Pawn* makePawn() noexcept
        {
            T* pw = new T();
            return pw;
        }

        template<typename T>
        inline static T* cast(Pawn* pw) noexcept
        {
            return static_cast<T*>(pw);
        }

        static void destroyPawn(Pawn* pw) noexcept;
    private:
        friend class GLPipeline;
    };
}
