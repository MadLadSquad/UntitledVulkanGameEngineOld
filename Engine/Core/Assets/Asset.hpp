// Asset.hpp
// Last update 1/8/2021 by Madman10K
#pragma once
#include <Core/Types.hpp>

namespace UVK
{
    enum AssetType
    {
        UVK_ASSET_TYPE_TEXTURE,
        UVK_ASSET_TYPE_SHADER,
        UVK_ASSET_TYPE_MODEL,
        UVK_ASSET_TYPE_AUDIO,
        UVK_ASSET_TYPE_FONT,
        UVK_ASSET_TYPE_VIDEO
    };

    template<typename T>
    struct Asset
    {
    public:
        String location;
        T* data;
    };
}