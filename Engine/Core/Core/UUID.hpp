#pragma once
#include <random>
#include <Core/Defines.hpp>

namespace UVK
{
    // A manager on top of the UUID system
    class UVK_PUBLIC_API IDManager
    {
    public:
        // Generates a UUID given a reference to a uint64_t
        static void generate(uint64_t& id) noexcept;
    private:
        void generateID(uint64_t& id) noexcept;
        std::random_device device;
        std::mt19937_64 engine = std::mt19937_64(device());
        std::uniform_int_distribution<uint64_t> uniformDistribution;
    };

    // A UUID storage class
    struct UVK_PUBLIC_API UUID
    {
    public:
        UUID() = default;
        // Generates a UUID
        void generate() noexcept;
        // Returns the UUID
        [[nodiscard]] const uint64_t& data() const noexcept;
    private:
        friend class Actor;
        friend class Level;
        uint64_t id = 0;
    };
}