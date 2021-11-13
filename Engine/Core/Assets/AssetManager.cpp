// AssetManager.cpp
// Last update 26/10/2021 by Madman10K
#include "AssetManager.hpp"
#include <Core/Defines.hpp>
#include <Core/Global.hpp>
#include <random>

void UVK::AssetManager::load()
{
#ifndef PRODUCTION
    loadRaw();
#else
    loadArchive();
#endif
}

#ifndef PRODUCTION
void UVK::AssetManager::loadRaw()
{
    std::random_device device;
    std::mt19937_64 engine(device());
    std::uniform_int_distribution<uint64_t> uniformDistribution;
    uniformDistribution(engine);

    for (auto& a : std_filesystem::recursive_directory_iterator(std_filesystem::path("../Content/")))
    {
        if (!a.is_directory())
        {
            Asset asset =
            {
                .name = a.path().filename().string(),
                .id = uniformDistribution(engine),
                .assetType = getAssetType(a.path()),
                .path = a.path().string()
            };
            assets.push_back(asset);
        }
    }
}
#endif

void UVK::AssetManager::loadArchive()
{

}

UVK::AssetType UVK::AssetManager::getAssetType(const std::filesystem::path& path)
{
    static constexpr const char* audioExtensions[] = { ".wav", ".flac", ".m4a", ".ogg", ".mp3" };
    static constexpr const char* imageExtensions[] = { ".jpeg", ".jpg", ".tiff", ".gif", ".bmp", ".png", ".tga", ".psd", ".pic" };
    static constexpr const char* videoExtensions[] = { ".mov", ".m4v", ".mp4", ".mpeg", ".mkv", ".mpg", ".wmv", ".webm" };
    static constexpr const char* objExtensions[] = { ".obj", ".fbx", ".glb", ".gltf", ".mp3" };
    static constexpr const char* codeExtensions[] = { ".yaml", ".uvklevel", ".yml" };

    for (auto& a : audioExtensions)
        if (path.filename().string() == std::string(a))
            return UVK::ASSET_TYPE_AUDIO;
    for (auto& a : imageExtensions)
        if (path.filename().string() == std::string(a))
            return UVK::ASSET_TYPE_TEXTURE;
    for (auto& a : videoExtensions)
        if (path.filename().string() == std::string(a))
            return UVK::ASSET_TYPE_VIDEO;
    for (auto& a : objExtensions)
        if (path.filename().string() == std::string(a))
            return UVK::ASSET_TYPE_MODEL;
    for (auto& a : codeExtensions)
        if (path.filename().string() == std::string(a))
            return UVK::ASSET_TYPE_CODE;
    if (path.filename().string() == ".ttf")
        return UVK::ASSET_TYPE_FONT;
    else if (path.filename().string() == ".vert" || path.filename().string() == ".frag" || path.filename().string() == ".gl" || path.filename().string() == ".glsl")
        return UVK::ASSET_TYPE_SHADER;

    return UVK::ASSET_TYPE_UNKNOWN;
}

UVK::AssetManager::~AssetManager()
{
    assets.clear();
}

std::vector<UVK::Asset> UVK::AssetManager::getAllAssetsWithName(const char* name)
{
    std::vector<Asset> vect;
    for (auto& a : global.assetManager.assets)
        if (a.name == std::string(name))
            vect.emplace_back(a);
    return vect;
}

std::vector<UVK::Asset> UVK::AssetManager::getAllAssetsOfType(UVK::AssetType type)
{
    std::vector<Asset> vect;
    for (auto& a : global.assetManager.assets)
        if (a.assetType == type)
            vect.emplace_back(a);
    return vect;
}
