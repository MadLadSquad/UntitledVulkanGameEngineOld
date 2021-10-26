// Asset.hpp
// Last update 26/10/2021 by Madman10K
#pragma once
#include <Core/Types.hpp>

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

    struct Asset
    {
        std::string name;
        uint64_t id;
        AssetType assetType;
#ifndef PRODUCTION
        std::string path;
#endif
    };
}