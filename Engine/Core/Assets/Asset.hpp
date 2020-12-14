// Asset.hpp
// Last update 12/7/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>

namespace UVK
{
    UVK_API struct AssetReference
    {
        String Name;
        String Location;
        int Type;
    };

    UVK_API class Asset
    {
    public:
        void AddAsset(int type, String location, String name)
        {
            switch (type)
            {
                case 0:
                    Serialise(type, location, name);
                case 1:
                    Serialise(type, location, name);
                case 2:
                    Serialise(type, location, name);
                case 3:
                    Serialise(type, location, name);
                case 4:
                    std::cout << "You are trying to serialise a level! Please use the level class instead of the asset class!" << std::endl;
                default:
                    std::cout << "You are trying to serialise an unknown asset type! Please use another asset type that is part of the standard!" << std::endl;
            }
        }

        AssetReference GetAsset(AssetReference asset, String location)
        {
            return Deserialise(location);
        }

    private:
        void Serialise(int type, String location, String name)
        {
            YAML::Emitter out;

            out << YAML::BeginMap;

            out << YAML::Key << "type" << YAML::Value << type;

            out << YAML::EndMap;
        }

        AssetReference Deserialise(String location)
        {
            AssetReference ref;

            YAML::Node asset = YAML::LoadFile(static_cast<std::string>(location) + ".yaml");

            if (asset["name"])
            {
                ref.Name = asset["name"].as<const char*>();
            }
            else
            {
                std::cout << "Invalid asset format" << std::endl;
                return ref;
            }

            if (asset["type"])
            {
                ref.Type = asset["name"].as<int>();
            }
            else
            {
                std::cout << "Invalid asset format" << std::endl;
                return ref;
            }

            if (asset["location"])
            {
                ref.Location = asset["location"].as<const char*>();
            }
            else
            {
                std::cout << "Invalid asset format" << std::endl;
                return ref;
            }

            return ref;
        }
    };
}
