// AudioComponent.cpp
// Last update 22/9/2021 by Madman10K
#include "AudioComponent.hpp"
#include "CoreComponent.hpp"
#include <Core/Actor.hpp>

void UVK::AudioComponent::create(UVK::Actor* act, const char* file)
{
    actor = act;
    currentFile = file;

    core = &actor->get<CoreComponent>();
}

void UVK::AudioComponent::tick()
{

}
