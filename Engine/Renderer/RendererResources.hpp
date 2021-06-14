#pragma once
#include <Core.hpp>

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
        bool bEditor;
    };

    inline RendererResources rendererResources;
}