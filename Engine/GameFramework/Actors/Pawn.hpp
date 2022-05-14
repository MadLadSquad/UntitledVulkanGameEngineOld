#pragma once
#include <Core.hpp>
#include <Renderer/Camera/Camera.hpp>
#include <Core/Actor.hpp>

namespace UVK
{
    /**
     * @brief an actor that the player can control
     * @var camera - A class for the camera
     * @var name - The name of the actor to attach to
     * @var id - The id of the actor to attach to
     * @var devName - The development name of the actor to attach to
     * @var actor - The actual actor ID to attach to
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
