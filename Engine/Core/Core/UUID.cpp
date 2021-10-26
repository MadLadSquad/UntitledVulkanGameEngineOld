// UUID.cpp
// Last update 26/10/2021 by Madman10K
#include "UUID.hpp"
#include "Global.hpp"

void UVK::IDManager::generateID(uint64_t& id)
{
    id = uniformDistribution(engine);
}

void UVK::IDManager::generate(uint64_t& id)
{
    global.idManager.generateID(id);
}

void UVK::UUID::generate()
{
    IDManager::generate(id);
}

const uint64_t& UVK::UUID::data()
{
    return id;
}