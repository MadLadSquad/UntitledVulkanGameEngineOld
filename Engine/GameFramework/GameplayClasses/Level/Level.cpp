// Level.cpp
// Last update 26/9/2021 by Madman10K
#include <GameFramework/Components/Components.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <Core/Actor.hpp>
#include <Events/Events.hpp>
#include <Engine/Core/Core/Global.hpp>
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

void UVK::Level::saveEntity(YAML::Emitter& out, entt::entity act)
{
    out << YAML::BeginMap;

    if (global.ecs.data().any_of<CoreComponent>(act))
    {
        auto& a = global.ecs.data().get<CoreComponent>(act);
        out << YAML::Key << "actor" << YAML::Value << a.name;
        out << YAML::Key << "id" << YAML::Value << a.id;
        out << YAML::Key << "dev-name" << YAML::Value << a.devName;
    }

    if (global.ecs.data().any_of<UVK::AudioComponent>(act))
    {
        auto& a = global.ecs.data().get<UVK::AudioComponent>(act);
        out << YAML::Key << "audio-pitch" << YAML::Value << a.source.audioData().pitch;
        out << YAML::Key << "audio-gain" << YAML::Value << a.source.audioData().gain;
        out << YAML::Key << "audio-loop" << YAML::Value << a.source.audioData().bLoop;
        out << YAML::Key << "audio-velocity" << YAML::Value << a.source.audioData().velocity;
        out << YAML::Key << "audio-file" << YAML::Value << a.source.audioData().location;
    }
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

    std::ofstream fileout(location + std::string(".uvklevel"));
    fileout << out.c_str();
}

void UVK::Level::openInternal(UVK::String location)
{
    YAML::Node out;
    try
    {
        out = YAML::LoadFile(location + std::string(".uvklevel"));
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Invalid level file location of file!", UVK_LOG_TYPE_ERROR);
        return;
    }

    for (const auto& a : global.ecs.data().view<AudioComponent>())
    {
        auto& audio = global.ecs.data().get<AudioComponent>(a);
        if (audio.source.state() != UVK_AUDIO_STATE_STOPPED)
            audio.stop();
    }
    ECS::each([](Actor& act)
    {
        act.destroy();
    });
    global.ecs.clear(); // Clear the ECS registry(contains all the actors)
    global.ui.clear(); // Clear the UI registry
    if (!global.bEditor)
    {
        Events::callEnd(); // If running in a game environment call all the end events
    }
    Events::clear(); // Reset all scriptable objects, clear the event queue and add them again

    logger.consoleLog("Opening level with location: ", UVK_LOG_TYPE_NOTE, location);

    // Load a bunch of metadata into the global state
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

            auto act = Actor(name, id, devName);

            if (entity["audio-pitch"] && entity["audio-gain"] && entity["audio-loop"] && entity["audio-velocity"] && entity["audio-file"])
            {
                auto& a = act.add<UVK::AudioComponent>();

                a.source.audioData().pitch = entity["audio-pitch"].as<float>();
                a.source.audioData().gain = entity["audio-gain"].as<float>();
                a.source.audioData().bLoop = entity["audio-loop"].as<bool>();
                a.source.audioData().velocity = entity["audio-velocity"].as<FVector>();
                a.source.audioData().location = entity["audio-file"].as<std::string>();
            }
        }
        logger.consoleLog("Iterated entities", UVK_LOG_TYPE_SUCCESS);
    }

    if (!global.bEditor)
    {
        Events::callBegin();
    }
}

UVK::FVector4& UVK::Level::getAmbientLighting()
{
    return global.ambientLight;
}

UVK::FVector4& UVK::Level::getSceneColour()
{
    return global.colour;
}

std::string& UVK::Level::getLevelName()
{
    return global.levelName;
}

void UVK::Level::endAutohandle() const
{
    gameMode->endPlay();
}

void UVK::Level::tickAutohandle(float deltaTime) const
{
    gameMode->tick(deltaTime);
}

void UVK::Level::beginAutohandle() const
{
    gameMode->beginPlay();
}

UVK::PlayerController* UVK::Level::getPlayerController(UVK::Level* lvl)
{
    return lvl->gameMode->playerController;
}

UVK::Pawn* UVK::Level::getPawn(UVK::Level* lvl)
{
    return lvl->gameMode->playerController->pawn;
}

UVK::GameState* UVK::Level::getGameState(UVK::Level* lvl)
{
    return lvl->gameMode->gameState;
}

UVK::PlayerState* UVK::Level::getPlayerState(UVK::Level* lvl)
{
    return lvl->gameMode->playerState;
}
