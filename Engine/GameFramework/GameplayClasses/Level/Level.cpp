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
        out << YAML::Key << "audio2d-repeat" << YAML::Value << a.bAudioRepeat;
    }

    if (pool.has<AudioComponent3D>(act))
    {
        auto& a = pool.get<AudioComponent3D>(act);

        out << YAML::Key << "audio3d-location" << YAML::Value << a.loc;
        out << YAML::Key << "audio3d-pitch" << YAML::Value << a.pitch;
        out << YAML::Key << "audio3d-gain" << YAML::Value << a.gain;
        out << YAML::Key << "audio3d-repeat" << YAML::Value << a.bAudioRepeat;
        out << YAML::Key << "audio3d-translation" << YAML::Value << a.trs;
    }

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
    id = 0;
    logger.consoleLog("Opening file", UVK_LOG_TYPE_NOTE);
    auto out = YAML::LoadFile(location);
    logger.consoleLog("Opened file with name:", UVK_LOG_TYPE_SUCCESS, out["name"].as<std::string>());
    auto entities = out["actors"];
    if (entities)
    {
        logger.consoleLog("Iterating entities", UVK_LOG_TYPE_NOTE);
        for (auto entity : entities)
        {
            auto name = entity["actor"].as<std::string>();

            auto act = pool.create();


            if (entity["audio3d-location"])
            {
                auto& a = registry.addComponent<AudioComponent3D>(act);

                a.play(entity["audio3d-location"].as<std::string>().c_str(), entity["audio3d-repeat"].as<bool>(), entity["audio3d-gain"].as<float>(), entity["audio3d-pitch"].as<float>(), entity["audio3d-translation"].as<FVector>());
            }

            if (entity["audio2d-location"])
            {
                auto& a = registry.addComponent<AudioComponent2D>(act);

                a.play(entity["audio2d-location"].as<std::string>().c_str(), entity["audio2d-repeat"].as<bool>(), entity["audio2d-gain"].as<float>(), entity["audio2d-pitch"].as<float>());
            }

            if (entity["mcr-translation"])
            {
                auto& a = registry.addComponent<MeshComponentRaw>(act);

                ShaderImportType type;

                if (entity["mcr-simport"].as<int>() == 0)
                {
                    type = SHADER_IMPORT_TYPE_FILE;
                }
                else if (entity["mcr-simport"].as<int>() == 1)
                {
                    type = SHADER_IMPORT_TYPE_STRING;
                }
                else
                {
                    type = SHADER_IMPORT_TYPE_SPIR;
                }

                a.createMesh(entity["mcr-vertices"].as<std::vector<float>>().data(), entity["mcr-indices"].as<std::vector<uint32_t>>().data(), entity["mcr-vertices"].as<std::vector<float>>().size(), entity["mcr-indices"].as<std::vector<int>>().size(), entity["mcr-vshader"].as<std::string>().c_str(), entity["mcr-fshader"].as<std::string>().c_str(), type);
            }
        }
        logger.consoleLog("Iterated entities", UVK_LOG_TYPE_SUCCESS);
    }
}