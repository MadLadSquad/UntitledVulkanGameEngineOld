#include "UUID.hpp"
#include "Global.hpp"

void UVK::IDManager::generateID(uint64_t& id) noexcept
{
    id = uniformDistribution(engine);
}

void UVK::IDManager::generate(uint64_t& id) noexcept
{
    global.idManager.generateID(id);
}

void UVK::UUID::generate() noexcept
{
    IDManager::generate(id);
}

const uint64_t& UVK::UUID::data() const noexcept
{
    return id;
}