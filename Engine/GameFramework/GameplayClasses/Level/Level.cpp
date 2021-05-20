// Level.cpp
// Last update 18/5/2021 by Madman10K
#include "../../Components/Components.hpp"
#include "Engine/Core/Core/Registry.hpp"
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

#ifndef __MINGW32__
    if (registry.hasComponent<UVK::AudioComponent>(act))
    {
        auto& a = registry.getComponent<UVK::AudioComponent>(act);
        out << YAML::Key << "audio-pitch" << YAML::Value << a.data.pitch;
        out << YAML::Key << "audio-gain" << YAML::Value << a.data.gain;
        out << YAML::Key << "audio-loop" << YAML::Value << a.data.bLoop;
        out << YAML::Key << "audio-location" << YAML::Value << a.data.position;
        out << YAML::Key << "audio-velocity" << YAML::Value << a.data.velocity;
        out << YAML::Key << "audio-file" << YAML::Value << a.data.location;
    }
#endif
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
}

void UVK::Level::open(String location) noexcept
{
    pool.clear();

    logger.consoleLog("Opening level with location: ", UVK_LOG_TYPE_NOTE, location);

    YAML::Node out;
    bool bValid = true;

    try
    {
        out = YAML::LoadFile(location);
    }
    catch (YAML::BadFile&)
    {
        bValid = false;
        logger.consoleLog("Invalid level file location of file!", UVK_LOG_TYPE_ERROR);
    }

    if (bValid)
    {
        logger.consoleLog("Opened file with name:", UVK_LOG_TYPE_SUCCESS, out["name"].as<std::string>());

        auto entities = out["actors"];
        if (entities)
        {
            logger.consoleLog("Iterating entities", UVK_LOG_TYPE_NOTE);
#if 0
            std::mutex mutex;
            std::vector<std::future<void>> vect;

            constexpr auto func = [](std::mutex* mx, const YAML::Node* ent)
            {
                auto name = (*ent)["actor"].as<std::string>();

                mx->lock();
                auto act = pool.create();
                auto& core = registry.addComponent<UVK::CoreComponent>(act);
                mx->unlock();

                core.name = name;
            };
#endif
            for (const YAML::Node& entity : entities)
            {
#if 0
                vect.push_back(std::async(std::launch::async, func, &mutex, &entity));
#else
                auto name = entity["actor"].as<std::string>();
                auto act = pool.create();
                auto& core = registry.addComponent<UVK::CoreComponent>(act);
                core.name = name;
                core.id = entity["id"].as<int>();

                if (entity["audio-pitch"] && entity["audio-gain"] && entity["audio-location"])
                {
                    auto& a = registry.addComponent<UVK::AudioComponent>(act);

                    UVK::AudioSourceData data;
                    data.pitch = entity["audio-pitch"].as<float>();
                    data.gain = entity["audio-gain"].as<float>();
                    data.bLoop = entity["audio-loop"].as<bool>();
                    data.position = entity["audio-location"].as<FVector>();
                    data.velocity = entity["audio-velocity"].as<FVector>();
                    data.location = entity["audio-file"].as<std::string>();

                    a.init(data);
                }
#endif
            }
            logger.consoleLog("Iterated entities", UVK_LOG_TYPE_SUCCESS);
        }
    }
}