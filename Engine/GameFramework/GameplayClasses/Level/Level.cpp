// Level.cpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)

#include "Level.hpp"

namespace YAML {

    template<>
    struct convert<glm::vec3>
    {
        static Node encode(const FVector& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, FVector& rhs)
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<FVector4>
    {
        static Node encode(const FVector4& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, FVector4& rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };

}

void UVK::Level::Save(String output)
{

}

// Operator overloads for future transform component
YAML::Emitter& operator<<(YAML::Emitter& out, const FVector& vect)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << YAML::EndSeq;
    return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const FVector4& vect)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << vect.w << YAML::EndSeq;
    return out;
}

void UVK::Level::Open(AssetReference assetRef)
{
    if (assetRef.Type == 4)
    {
        Log.ConsoleLog("A level asset was passed", NOTE);

        YAML::Node file = YAML::LoadFile(assetRef.Location);

        if (file["name"])
        {
            assetRef.Name = file["name"].as<std::string>();
        }

        if (true)
        {

        }
    }
    else
    {
        Log.ConsoleLog("An invalid asset type was passed as level. If you are a user contact the developer of the application about this. If you are a developer use the ASSET_TYPE macros instead of plane integers and monitor what asset types you are passing to the given asset function!", ERROR);
    }
}

void UVK::Level::SaveEntity(YAML::Emitter& out, Actor act)
{

}
