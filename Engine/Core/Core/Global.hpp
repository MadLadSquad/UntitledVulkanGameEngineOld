// RendererResources.hpp
// Last update 30/6/2021 by Madman10K
#pragma once
#include <Core/ECS.hpp>
#include <Core.hpp>
#include <Renderer/Window/Window.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>
#include <GameFramework/Actors/ActorManager.hpp>

namespace UVK
{
    struct UVKGlobal
    {
        UVKGlobal()
        {
            colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
            actorManager.init();
        }

        ~UVKGlobal()
        {
            actorManager.destroy();
        }
        FVector4 colour{};
        FVector4 ambientLight{};
        std::string levelName;
        bool bEditor{};
        bool bUsesVulkan{};
        GameInstance* instance;
        Window window;
        ECSManager ecs;
        UVK::ActorManager actorManager;
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