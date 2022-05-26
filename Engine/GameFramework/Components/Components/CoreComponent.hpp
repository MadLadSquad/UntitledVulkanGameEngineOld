#pragma once
#include <iostream>
#include <Core/Types.hpp>
#include <Core/UUID.hpp>

namespace UVK
{
    class Actor;
    /**
     * @brief The base component every entity has
     * @param name, id, devName - used for identification of entities
     */
    struct CoreComponent
    {
        UVK::FString name;
        uint64_t id = 0;
        UVK::FString devName;

        FVector translation = { 0.0f, 0.0f, 0.0f };
        FVector rotation = { 0.0f, 0.0f, 0.0f };
        FVector scale = { 1.0f, 1.0f, 1.0f };

        UUID uuid;
        [[nodiscard]] const bool& standart() const noexcept
        {
            return bHasUUID;
        }
        bool bHasUUID = true;
    private:
        friend class Level;

        void saveToLevel(YAML::Emitter& out) const noexcept;
        static void openToLevel(Actor& actor, const YAML::Node& entity) noexcept;

    };
}