// RendererResources.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <glm/glm/gtx/quaternion.hpp>

namespace UVK
{
    struct RendererResources
    {
        RendererResources()
        {
            colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
        }

        FVector4 colour{};
        FVector4 ambientLight{};
        std::string levelName;
        bool bEditor{};
        bool bUsesVulkan{};
    };

    inline RendererResources rendererResources;

    class Math
    {
    public:
        static void translate(glm::mat4& mat, FVector vt)
        {
            if (rendererResources.bUsesVulkan)
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
            if (rendererResources.bUsesVulkan)
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
            if (rendererResources.bUsesVulkan)
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