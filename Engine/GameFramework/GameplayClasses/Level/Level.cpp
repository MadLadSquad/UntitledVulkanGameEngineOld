// Level.cpp
// Last update 3/17/2021 by Madman10K

#include "Level.hpp"

// Creates bindings for a FVector
namespace YAML {

    template<>
    struct convert<UVK::FVector>
    {
        static Node encode(const UVK::FVector& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UVK::FVector& rhs)
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
    struct convert<UVK::FVector4>
    {
        static Node encode(const UVK::FVector4& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UVK::FVector4& rhs)
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
// Operator overloads for future transform component
YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector& vect)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << YAML::EndSeq;
    return out;
}
YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector4& vect)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << vect.w << YAML::EndSeq;
    return out;
}

void UVK::Level::saveEntity(YAML::Emitter& out, Actor act)
{
    out << YAML::BeginMap;

    if (pool.has<CoreComponent>(act))
    {
        auto& a = pool.get<CoreComponent>(act);
        out << YAML::Key << "actor" << YAML::Value << a.name;
        out << YAML::Key << "id" << YAML::Value << a.id;
    }

    if (pool.has<AudioComponent2D>(act))
    {
        auto& a = pool.get<AudioComponent2D>(act);

        out << YAML::Key << "audio2d-location" << YAML::Value << a.loc;
        out << YAML::Key << "audio2d-pitch" << YAML::Value << a.pitch;
        out << YAML::Key << "audio2d-gain" << YAML::Value << a.gain;
        out << YAML::Key << "audio2d-repeat" << YAML::Value << a.bRepeat;
    }

    if (pool.has<MeshComponentRaw>(act))
    {
        auto& a = pool.get<MeshComponentRaw>(act);
    }

    out << YAML::EndMap;
}

void UVK::Level::save(String location, String name)
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "name" << YAML::Value << name;
    out << YAML::Key << "actors" << YAML::Value << YAML::BeginSeq;
    pool.each([&](auto entityID)
    {
        saveEntity(out, entityID);
    });
    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fileout(location);
    fileout << out.c_str();
    //fileout.close();
}

void UVK::Level::open(String location) noexcept
{
    pool.clear();
    id = 0;
    logger.consoleLog("Opening file", NOTE);
    auto out = YAML::LoadFile(location);
    logger.consoleLogComplex<const char*>("Opened file with name:", SUCCESS, { out["name"].as<std::string>().c_str() });
    auto entities = out["actors"];
    if (entities)
    {
        logger.consoleLog("Iterating entities", NOTE);
        for (auto entity : entities)
        {
            auto name = entity["actor"].as<std::string>();

            registry.createActor(name);

            //Actor act = pool.create();

            //if ()
            //{
            //    auto& a = pool.emplace<CoreComponent>(act);
            //    //a.id = id.as<uint64_t>();
            //    //a.name = name;
            //}
            //{
            //    auto& a = pool.emplace<AudioComponent2D>(act);
            //}


        }
        logger.consoleLog("Iterated entities", SUCCESS);
    }
}