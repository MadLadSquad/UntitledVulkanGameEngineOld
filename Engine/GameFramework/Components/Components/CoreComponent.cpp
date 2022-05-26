#include "CoreComponent.hpp"
#include <Core/Actor.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML
{
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
extern YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector& vect) noexcept;
extern YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector4& vect) noexcept;

void UVK::CoreComponent::saveToLevel(YAML::Emitter& out) const noexcept
{
    out << YAML::Key << "actor" << YAML::Value << name;
    out << YAML::Key << "id" << YAML::Value << id;
    out << YAML::Key << "dev-name" << YAML::Value << devName;
    out << YAML::Key << "uuid" << YAML::Value << uuid.data();
    out << YAML::Key << "standart" << YAML::Value << standart();
    out << YAML::Key << "translation" << YAML::Value << translation;
    out << YAML::Key << "rotation" << YAML::Value << rotation;
    out << YAML::Key << "scale" << YAML::Value << scale;
}

void UVK::CoreComponent::openToLevel(UVK::Actor& actor, const YAML::Node &entity) noexcept
{
    if (entity["actor"] && entity["id"] && entity["dev-name"] && entity["uuid"] && entity["standart"] && entity["translation"] && entity["rotation"] && entity["scale"])
    {
        actor.create(entity["actor"].as<FString>(), entity["id"].as<uint64_t>(), entity["dev-name"].as<FString>());
        auto& core = actor.get<CoreComponent>();

        core.uuid.id = entity["uuid"].as<uint64_t>();
        core.bHasUUID = entity["standart"].as<bool>();
        core.translation = entity["translation"].as<FVector>();
        core.rotation = entity["rotation"].as<FVector>();
        core.scale = entity["scale"].as<FVector>();
    }
}