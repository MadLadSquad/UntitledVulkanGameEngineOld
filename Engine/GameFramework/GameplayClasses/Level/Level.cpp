// Level.cpp
// Last update 6/7/2021 by Madman10K
#include "../../Components/Components.hpp"
#include "Engine/Core/Core/Actor.hpp"
#include <Events/Events.hpp>
#include <Engine/Core/Core/Global.hpp>

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

void UVK::Level::saveEntity(YAML::Emitter& out, entt::entity act)
{
    out << YAML::BeginMap;

    if (global.ecs.data().has<CoreComponent>(act))
    {
        auto& a = global.ecs.data().get<CoreComponent>(act);
        out << YAML::Key << "actor" << YAML::Value << a.name;
        out << YAML::Key << "id" << YAML::Value << a.id;
        out << YAML::Key << "dev-name" << YAML::Value << a.devName;
    }

#ifndef __MINGW32__
    if (global.ecs.data().has<UVK::AudioComponent>(act))
    {
        auto& a = global.ecs.data().get<UVK::AudioComponent>(act);
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

void UVK::Level::save(String location)
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "name" << YAML::Value << global.levelName;
    out << YAML::Key << "background-colour" << YAML::Value << global.colour;
    out << YAML::Key << "ambient-light" << YAML::Value << global.ambientLight;
    out << YAML::Key << "actors" << YAML::Value << YAML::BeginSeq;
    global.ecs.data().each([&](auto entityID)
    {
        const auto& b = global.ecs.data().get<CoreComponent>(entityID);

        if (b.id != 330 && b.name.find("Editor") == std::string::npos)
        {
            saveEntity(out, entityID);
        }
    });
    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fileout(location);
    fileout << out.c_str();
}

void UVK::Level::open(String location) noexcept
{
    global.ecs.clear();
    if (!global.bEditor)
    {
        global.events.callEnd();
        global.ui.clear();
    }

    global.events.clear();

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
        global.levelName = out["name"].as<std::string>();
        global.levelLocation = location;
        logger.consoleLog("Opened file with name: ", UVK_LOG_TYPE_SUCCESS, global.levelName);
        global.colour = out["background-colour"].as<FVector4>();
        global.ambientLight = out["ambient-light"].as<FVector4>();
        auto entities = out["actors"];
        if (entities)
        {
            logger.consoleLog("Iterating entities", UVK_LOG_TYPE_NOTE);

            for (const YAML::Node& entity : entities)
            {
                auto name = entity["actor"].as<std::string>();
                auto id = entity["id"].as<uint64_t>();
                auto devName = entity["dev-name"].as<std::string>();
                if (id == 330 && name.find("Editor") == std::string::npos)
                {
                    id = 331;
                }
                auto act = Actor(name, id, devName, true);

                if (entity["audio-pitch"] && entity["audio-gain"] && entity["audio-location"])
                {
                    auto& a = act.add<UVK::AudioComponent>();

                    UVK::AudioSourceData data;
                    data.pitch = entity["audio-pitch"].as<float>();
                    data.gain = entity["audio-gain"].as<float>();
                    data.bLoop = entity["audio-loop"].as<bool>();
                    data.position = entity["audio-location"].as<FVector>();
                    data.velocity = entity["audio-velocity"].as<FVector>();
                    data.location = entity["audio-file"].as<std::string>();

                    a.init(data);
                }
            }
            logger.consoleLog("Iterated entities", UVK_LOG_TYPE_SUCCESS);
        }

        if (!global.bEditor)
        {
            global.events.callBegin();
        }
    }
}