// Level.cpp
// Last update 1/10/2021 by Madman10K

#include "Level.hpp"

// Creates bindings for a FVector
namespace YAML {

    template<>
    struct convert<FVector>
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

void UVK::Level::saveEntity(YAML::Emitter& out, Actor act)
{
    out << YAML::BeginMap;

    if (pool.has<CoreComponent>(act))
    {
        auto& a = pool.get<CoreComponent>(act);
        out << YAML::Key << "actor" << YAML::Value << a.name;
        out << YAML::Key << "id" << YAML::Value << a.id;
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

void UVK::Level::open(const char* location)
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
            //if (id)
            //{
            //    auto& a = pool.emplace<CoreComponent>(act);
            //    //a.id = id.as<uint64_t>();
            //    //a.name = name;
            //}
        }
        logger.consoleLog("Iterated entities", SUCCESS);
    }
}