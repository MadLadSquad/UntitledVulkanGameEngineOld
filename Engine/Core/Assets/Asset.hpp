// Asset.hpp
// Last update 12/7/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>

namespace UVK
{
    UVK_API struct AssetReference
    {
        std::string Name;
        std::string Location;
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
                    break;
                case 1:
                    Serialise(type, location, name);
                    break;
                case 2:
                    Serialise(type, location, name);
                    break;
                case 3:
                    Serialise(type, location, name);
                    break;
                case 4:
                    Log.ConsoleLog("You are trying to serialise a level! Please use the level class instead of the asset class!", ERROR);
                    break;
                default:
                    Log.ConsoleLog("You are trying to serialise an unknown asset type! Please use another asset type that is part of the standard!", ERROR);
                    break;
            }
        }

        AssetReference GetAsset(String location)
        {
            return Deserialise(location);
        }

    private:
        void Serialise(int type, String location, String name)
        {
            YAML::Emitter out;
            out << YAML::BeginMap;

            out << YAML::Key << "type" << YAML::Value << type;
            out << YAML::Key << "name" << YAML::Value << name;
            out << YAML::Key << "location" << YAML::Value << location;

            out << YAML::EndMap;

            std::ofstream assetOut(static_cast<std::string>(location)+static_cast<std::string>(name)+".yaml");
            assetOut << out.c_str();

            assetOut.close();
        }

        AssetReference Deserialise(String location)
        {
            AssetReference ref;

            YAML::Node asset = YAML::LoadFile(static_cast<std::string>(location) + ".yaml");

            if (asset["name"])
            {
                ref.Name = asset["name"].as<std::string>();
            }
            else
            {
                Log.ConsoleLog("Invalid asset format", ERROR);
                return ref;
            }

            if (asset["type"])
            {
                ref.Type = std::stoi(asset["type"].as<std::string>());
            }
            else
            {
                Log.ConsoleLog("Invalid asset format", ERROR);
                return ref;
            }

            if (asset["location"])
            {
                ref.Location = asset["location"].as<std::string>();
            }
            else
            {
                Log.ConsoleLog("Invalid asset format", ERROR);
                return ref;
            }

            return ref;
        }
    };
}
