#pragma once
#include <random>
#include <Core/Defines.hpp>

namespace UVK
{
    class UVK_PUBLIC_API IDManager
    {
    public:
        static void generate(uint64_t& id) noexcept;
    private:
        void generateID(uint64_t& id) noexcept;
        std::random_device device;
        std::mt19937_64 engine = std::mt19937_64(device());
        std::uniform_int_distribution<uint64_t> uniformDistribution;
    };

    struct UVK_PUBLIC_API UUID
    {
    public:
        UUID() = default;
        void generate() noexcept;
        const uint64_t& data() const noexcept;
    private:
        friend class Actor;
        friend class Level;
        uint64_t id = 0;
    };
}