// AssetManager.hpp
// Last update 26/10/2021 by Madman10K
#pragma once
#include <unordered_map>
#include "Asset.hpp"
#include <Renderer/Textures/Texture.hpp>
#include <Renderer/OpenGL/Components/GLShader.hpp>
#include <Audio/Audio.hpp>

namespace UVK
{
    class AssetManager
    {
    public:
        static void findAsset(const std::string& name);
        void load();
    private:
#ifndef PRODUCTION
        // Generates an asset layout archive file and records all the IDs
        void loadRaw();
#endif
        // The asset archive is already there with all the assets, and we just load it from disk
        // but also loading the IDs from a layout file
        void loadArchive();
        std::vector<Asset> assets;
        static AssetType getAssetType(const std_filesystem::path& path);
    };
}