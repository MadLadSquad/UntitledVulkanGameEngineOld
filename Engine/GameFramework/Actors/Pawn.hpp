// Pawn.hpp
// Last update 22/9/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <Renderer/Camera/Camera.hpp>
#include <Core/Actor.hpp>

namespace UVK
{
    /**
     * @brief an actor that the player can control
     */
    class Pawn
    {
    public:
        Pawn() = default;

        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        virtual ~Pawn();
        Camera camera;

        std::string name;
        int64_t id{};
        std::string devName;

        Actor actor{};

        template<typename T>
        static Pawn* makePawn()
        {
            T* pw = new T();
            return pw;
        }

        template<typename T>
        static T* cast(Pawn* pw)
        {
            return static_cast<T*>(pw);
        }

        static void destroyPawn(Pawn* pw);
    private:
        friend class GLPipeline;
    };
}
