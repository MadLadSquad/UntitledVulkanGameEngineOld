#include <GameFramework/Components/Components.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <Core/Actor.hpp>
#include <Events/Events.hpp>
#include <Engine/Core/Core/Global.hpp>
#include "Level.hpp"
#include <Renderer/EditorUI/Widgets/Windows/SceneHierarchy.hpp>

// Creates bindings for a FVector
namespace YAML {

    template<>
    struct convert<UVK::FVector>
    {
        static Node encode(const UVK::FVector& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UVK::FVector& rhs) noexcept
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
        static Node encode(const UVK::FVector4& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UVK::FVector4& rhs) noexcept
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
YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector& vect) noexcept
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << YAML::EndSeq;
    return out;
}
YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector4& vect) noexcept
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << vect.w << YAML::EndSeq;
    return out;
}

void UVK::Level::saveEntity(YAML::Emitter& out, entt::entity act) noexcept
{
    out << YAML::BeginMap;

    if (global.ecs.data().any_of<CoreComponent>(act))
        global.ecs.data().get<CoreComponent>(act).saveToLevel(out);

    for (auto& a : global.instance->editor->currentLevelFolders)
    {
        for (auto& b : a.contents)
        {
            if (b == act)
            {
                out << YAML::Key << "sh-folder-name" << YAML::Value << a.name.c_str();
                goto exit_folder_setting;
            }
        }
    }
exit_folder_setting:
    if (global.ecs.data().any_of<UVK::AudioComponent>(act))
        global.ecs.data().get<UVK::AudioComponent>(act).saveToLevel(out);
    if (global.ecs.data().any_of<UVK::MeshComponent>(act))
        global.ecs.data().get<UVK::MeshComponent>(act).saveToLevel(out);

    out << YAML::EndMap;
}

void UVK::Level::save(String location) noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "name" << YAML::Value << global.levelName.c_str();
    out << YAML::Key << "background-colour" << YAML::Value << global.colour;
    out << YAML::Key << "ambient-light" << YAML::Value << global.ambientLight;
    out << YAML::Key << "actors" << YAML::Value << YAML::BeginSeq;
    global.ecs.data().each([&](auto entityID)
    {
        const auto& b = global.ecs.data().get<CoreComponent>(entityID);
        if (b.standart())
            saveEntity(out, entityID);
    });
    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fileout((location + UVK::FString(".uvklevel")).c_str());
    fileout << out.c_str();
}

void UVK::Level::openInternal(UVK::String location, bool first) noexcept
{
    YAML::Node out;
    try
    {
        out = YAML::LoadFile(location + UVK::FString(".uvklevel"));
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Invalid level file location of file!", UVK_LOG_TYPE_ERROR);
        return;
    }

    if (!first)
    {
        //for (const auto& a : global.ecs.data().view<AudioComponent>())
        //{
        //    auto& audio = global.ecs.data().get<AudioComponent>(a);
        //    if (audio.source.state() != UVK_AUDIO_STATE_STOPPED)
        //        audio.stop();
        //}
        global.ecs.clear(); // Clear the ECS registry(contains all the actors)
        global.ui.clear(); // Clear the UI registry
        if (!global.bEditor)
            Events::callEnd(); // If running in a game environment call all the end events
        Events::clear(); // Reset all scriptable objects, clear the event queue and add them again

        // This thing should not compile if we're compiling for production and also shouldn't run if we're running without the editor
#ifndef PRODUCTION
        if (global.bEditor)
        {
            Actor temp = Actor();
            int tmpInt = 1;
            bool tmpBool = true;
            SceneHierarchy::display(temp, tmpInt, tmpBool, global.instance->editor->currentLevelFolders, true);
        }
#endif
    }

    Logger::log("Opening level with location: ", UVK_LOG_TYPE_NOTE, location);

    // Load a bunch of metadata into the global state
    global.levelName = out["name"].as<std::string>();
    global.levelLocation = location;
    Logger::log("Opened file with name: ", UVK_LOG_TYPE_SUCCESS, global.levelName);
    global.colour = out["background-colour"].as<FVector4>();
    global.ambientLight = out["ambient-light"].as<FVector4>();

    auto entities = out["actors"];
    if (entities)
    {
        Logger::log("Iterating entities", UVK_LOG_TYPE_NOTE);

        for (const YAML::Node& entity : entities)
        {
            Actor act;
            UVK::CoreComponent::openToLevel(act, entity);

            if (entity["sh-folder-name"] && global.bEditor)
            {
                for (auto& a : global.instance->editor->currentLevelFolders)
                {
                    if (a.name == entity["sh-folder-name"].as<std::string>())
                    {
                        a.contents.emplace_back(act);
                        goto escape_editor_folders;
                    }
                }

                UVK::EditorFolder folder =
                {
                    .name = entity["sh-folder-name"].as<std::string>(),
                    .bValid = true,
                    .contents = { act }
                };
                global.instance->editor->currentLevelFolders.emplace_back(folder);
            }
escape_editor_folders:
            UVK::AudioComponent::openToLevel(act, entity);
            UVK::MeshComponent::openFromLevel(act, entity);
        }
        Logger::log("Iterated entities", UVK_LOG_TYPE_SUCCESS);
    }

    if (!global.bEditor)
        Events::callBegin();
}

UVK::FVector4& UVK::Level::getAmbientLighting() noexcept
{
    return global.ambientLight;
}

UVK::FVector4& UVK::Level::getSceneColour() noexcept
{
    return global.colour;
}

UVK::FString& UVK::Level::getLevelName() noexcept
{
    return global.levelName;
}

void UVK::Level::endAutohandle() const noexcept
{
    gameMode->endPlay();
}

void UVK::Level::tickAutohandle(float deltaTime) const noexcept
{
    gameMode->tick(deltaTime);
}

void UVK::Level::beginAutohandle() const noexcept
{
    gameMode->beginPlay();
}

UVK::PlayerController* UVK::Level::getPlayerController(UVK::Level* lvl) noexcept
{
    return lvl->gameMode->playerController;
}

UVK::Pawn* UVK::Level::getPawn(UVK::Level* lvl) noexcept
{
    return lvl->gameMode->playerController->pawn;
}

UVK::GameState* UVK::Level::getGameState(UVK::Level* lvl) noexcept
{
    return lvl->gameMode->gameState;
}

UVK::PlayerState* UVK::Level::getPlayerState(UVK::Level* lvl) noexcept
{
    return lvl->gameMode->playerState;
}
