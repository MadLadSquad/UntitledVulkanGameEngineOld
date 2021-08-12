// AssetManager.cpp
// Last update 12/8/2021 by Madman10K
#include <GL/glew.h>
#include "AssetManager.hpp"
#include <Core/Defines.hpp>
#include <Core/Global.hpp>

void UVK::AssetManager::loadRaw()
{
#ifndef __MINGW32__

    std_filesystem::path path("../Content/");

    constexpr const char* audioExtensions[] = { ".wav", ".flac", ".m4a", ".ogg", ".mp3" };
    constexpr const char* imageExtensions[] = { ".jpeg", ".jpg", ".tiff", ".gif", ".bmp", ".png", ".tga", ".psd", ".pic" };
    constexpr const char* videoExtensions[] = { ".mov", ".m4v", ".mp4", ".mpeg", ".mkv", ".mpg", ".wmv", ".webm" };
    constexpr const char* objExtensions[] = { ".obj", ".fbx", ".glb", ".gltf", ".mp3" };

    for (auto& a : std_filesystem::recursive_directory_iterator(path))
    {
        if (!a.is_directory())
        {
            bool bFound = false;

            for (auto& b : audioExtensions)
            {
                if (a.path().extension().string() == b)
                {
                    Asset<AudioSource> audioAsset = {};
                    audioAsset.location = a.path().extension().string().c_str();
                    audioAsset.data = nullptr;
                    audio.push_back(audioAsset);
                    bFound = true;
                }
            }

            if (!bFound)
            {
                for (auto& b : imageExtensions)
                {
                    if (a.path().extension().string() == b)
                    {
                        Asset<Texture> textureAsset;
                        textureAsset.location = a.path().string();
                        textureAsset.data = nullptr;

                        textures.push_back(textureAsset);
                    }
                }
            }
        }
    }

    /*for (auto& a : std_filesystem::directory_iterator(std_filesystem::path("../Generated/Shaders/")))
    {
        if (!a.is_directory())
        {
            if (a.path().extension().string() == ".glspv")
            {

            }
        }
    }*/
    //for

    /*
    for (auto& a : std_filesystem::recursive_directory_iterator(path))
    {
        if (!a.is_directory())
        {
            bool bFound;

            for (auto& b : audioExtensions)
            {
                if (a.path().extension().string() == b)
                {
                    bFound = true;
                    Asset asset{};
                    asset.location = a.path().string().c_str();
                    assetMap[UVK_ASSET_TYPE_AUDIO].push_back(asset);
                }
            }

            if (!bFound)
            {
                for (auto& b : imageExtensions)
                {
                    if (a.path().extension().string() == b)
                    {
                        bFound = true;
                        Asset asset{};
                        asset.location = a.path().string().c_str();
                        assetMap[UVK_ASSET_TYPE_TEXTURE].push_back(asset);
                    }
                }
            }

            if (!bFound)
            {
                for (auto& b : videoExtensions)
                {
                    if (a.path().extension().string() == b)
                    {
                        bFound = true;
                        Asset asset{};
                        asset.location = a.path().string().c_str();
                        assetMap[UVK_ASSET_TYPE_VIDEO].push_back(asset);
                    }
                }
            }

            if (!bFound)
            {
                for (auto& b : objExtensions)
                {
                    if (a.path().extension().string() == b)
                    {
                        bFound = true;
                        Asset asset{};
                        asset.location = a.path().string().c_str();
                        assetMap[UVK_ASSET_TYPE_MODEL].push_back(asset);
                    }
                }
            }

            if (!bFound)
            {
                if (a.path().extension().string() == ".ttf")
                {
                    bFound = true;
                    Asset asset{};
                    asset.location = a.path().string().c_str();
                    assetMap[UVK_ASSET_TYPE_FONT].push_back(asset);
                }
            }

            if (!bFound)
            {
                if (a.path().extension().string() == ".spv")
                {
                    bFound = true;
                    Asset asset{};
                    asset.location = a.path().string().c_str();

                    assetMap[UVK_ASSET_TYPE_SHADER].push_back(asset);
                }
            }

            if (!bFound)
            {
                Asset asset{};
                asset.location = a.path().string().c_str();
                assetMap[UVK_ASSET_TYPE_UNKNOWN].push_back(asset);
            }
        }
    }*/
#endif
}

void UVK::AssetManager::loadArchive()
{
    loadRaw();
}

const std::vector<UVK::Asset<UVK::Texture>>& UVK::Assets::textures()
{
    return global.assetManager.textures;
}

const std::vector<UVK::Asset<UVK::GLShader>>& UVK::Assets::shaders()
{
    return global.assetManager.shaders;
}

const std::vector<UVK::Asset<UVK::AudioSource>>& UVK::Assets::audio()
{
    return global.assetManager.audio;
}
