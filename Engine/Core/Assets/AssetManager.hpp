// AssetManager.hpp
// Last update 1/8/2021 by Madman10K
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
        AssetManager() = default;
    private:
        void loadRaw();
        // Archives are currently not supported but will be in development after 1.0
        void loadArchive();

        //std::unordered_map<AssetType, std::vector<Asset>> assetMap;
        std::vector<Asset<Texture>> textures;
        std::vector<Asset<GLShader>> shaders;
        std::vector<Asset<AudioSource>> audio;

        friend class Assets;
        friend class UVKGlobal;
    };

    class Assets
    {
    public:
        //template<typename T>
        //static const std::vector<Asset<T>>& getAllAssetsOfType(AssetType type);
    };
}