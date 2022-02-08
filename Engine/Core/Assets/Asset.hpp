// Asset.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <Core/Types.hpp>
#include <Core/Defines.hpp>

namespace UVK
{
    enum AssetType
    {
        ASSET_TYPE_TEXTURE,
        ASSET_TYPE_MODEL,
        ASSET_TYPE_AUDIO,
        ASSET_TYPE_VIDEO,
        ASSET_TYPE_CODE,
        ASSET_TYPE_FONT,
        ASSET_TYPE_SHADER,
        ASSET_TYPE_UNKNOWN
    };

    struct UVK_PUBLIC_API Asset
    {
        std::string name;
        uint64_t id;
        AssetType assetType;
#ifndef PRODUCTION
        std::string path;
#endif
    };
}