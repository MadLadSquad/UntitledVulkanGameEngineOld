// UUID.hpp
// Last update 26/10/2021 by Madman10K
#pragma once
#include <random>

namespace UVK
{
    class IDManager
    {
    public:
        static void generate(uint64_t& id);
    private:
        void generateID(uint64_t& id);
        std::random_device device;
        std::mt19937_64 engine = std::mt19937_64(device());
        std::uniform_int_distribution<uint64_t> uniformDistribution;
    };

    struct UUID
    {
    public:
        UUID() = default;
        void generate();
        const uint64_t& data();
    private:
        friend class Actor;
        friend class Level;
        uint64_t id = 0;
    };
}