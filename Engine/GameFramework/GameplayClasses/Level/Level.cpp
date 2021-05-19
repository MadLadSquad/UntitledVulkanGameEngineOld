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

    //if (pool.has<AudioComponent2D>(act))
    //{
    //    auto& a = pool.get<AudioComponent2D>(act);
    //    out << YAML::Key << "audio2d-location" << YAML::Value << a.loc;
    //    out << YAML::Key << "audio2d-pitch" << YAML::Value << a.pitch;
    //    out << YAML::Key << "audio2d-gain" << YAML::Value << a.gain;
    //    out << YAML::Key << "audio2d-repeat" << YAML::Value << a.bAudioRepeat;
    //}

    //if (pool.has<AudioComponent3D>(act))
    //{
    //    auto& a = pool.get<AudioComponent3D>(act);
    //    out << YAML::Key << "audio3d-location" << YAML::Value << a.loc;
    //    out << YAML::Key << "audio3d-pitch" << YAML::Value << a.pitch;
    //    out << YAML::Key << "audio3d-gain" << YAML::Value << a.gain;
    //    out << YAML::Key << "audio3d-repeat" << YAML::Value << a.bAudioRepeat;
    //    out << YAML::Key << "audio3d-translation" << YAML::Value << a.trs;
    //}

    if (pool.has<MeshComponentRaw>(act))
    {
        auto& a = pool.get<MeshComponentRaw>(act);

        out << YAML::Key << "mcr-translation" << YAML::Value << a.translation;
        out << YAML::Key << "mcr-rotation" << YAML::Value << a.rotation;
        out << YAML::Key << "mcr-scale" << YAML::Value << a.scale;
        out << YAML::Key << "mcr-vertices" << YAML::Value << a.vertex;
        out << YAML::Key << "mcr-indices" << YAML::Value << a.index;
        out << YAML::Key << "mcr-fshader" << YAML::Value << a.fShader;
        out << YAML::Key << "mcr-vshader" << YAML::Value << a.vShader;

        switch (a.impType)
        {
        case SHADER_IMPORT_TYPE_SPIR:
            out << YAML::Key << "mcr-simport" << YAML::Value << 2;
            break;
        case SHADER_IMPORT_TYPE_STRING:
            out << YAML::Key << "mcr-simport" << YAML::Value << 1;
            break;
        case SHADER_IMPORT_TYPE_FILE:
            out << YAML::Key << "mcr-simport" << YAML::Value << 0;
            break;
        }
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
#endif
            }
            logger.consoleLog("Iterated entities", UVK_LOG_TYPE_SUCCESS);
        }
    }
}