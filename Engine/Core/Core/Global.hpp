// RendererResources.hpp
// Last update 30/6/2021 by Madman10K
#pragma once
#include <Core/ECS.hpp>
#include <Core.hpp>
#include <Renderer/Window/Window.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <Renderer/UI/UI.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <Events/Events.hpp>

namespace UVK
{
    struct UVKGlobal
    {
        UVKGlobal()
        {
            colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
            actorManager.init();
        }

        template<typename T>
        void openNewLevel(String name)
        {
            func = [=](){
                const char* loc = name;
                level->endPlay();
                delete level;

                T* lvl = new T();
                level = lvl;
                T::open(loc);
                level->beginPlay();
            };
        }

        ~UVKGlobal()
        {
            delete level;
            actorManager.destroy();
        }

        FVector4 colour{};
        FVector4 ambientLight{};

        std::string levelName;
        std::string levelLocation;

        bool bEditor{};
        bool bUsesVulkan{};

        GameInstance* instance{};
        Window window;
        ECSManager ecs;

        UI ui;
        Level* level = nullptr;
    private:
        friend class GLPipeline;
        friend class Window;
        friend class Input;
        friend class Actor;
        friend class Level;

        UVK::Events events;
        UVK::ActorManager actorManager;
        std::vector<InputAction> inputActionList;
        std::function<void(void)> func = [=](){};

        void finalizeOpening()
        {
            func();

            func = [=](){};
        }
    };

    inline UVKGlobal global;

    class Math
    {
    public:
        static void translate(glm::mat4& mat, FVector vt)
        {
            if (global.bUsesVulkan)
            {
                mat = glm::translate(mat, FVector(vt.x, -vt.y, vt.z));
            }
            else
            {
                mat = glm::translate(mat, vt);
            }
        }

        static void rotate(glm::mat4& mat, FVector vt)
        {
            if (global.bUsesVulkan)
            {
                auto rot = glm::toMat4(glm::quat(FVector(vt.x, -vt.y, vt.z)));
                mat *= rot;
            }
            else
            {
                auto rot = glm::toMat4(glm::quat(vt));
                mat *= rot;
            }
        }

        static void scale(glm::mat4& mat, FVector vt)
        {
            if (global.bUsesVulkan)
            {
                mat = glm::scale(mat, FVector(vt.x, -vt.y, vt.z));
            }
            else
            {
                mat = glm::scale(mat, vt);
            }
        }
    };
}