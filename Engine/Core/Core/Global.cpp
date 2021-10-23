// Global.cpp
// Last update 22/9/2021 by Madman10K
#include "Global.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <glm/glm/gtx/quaternion.hpp>

UVK::UVKGlobal::UVKGlobal()
{
    colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
#ifdef PRODUCTION
    assetManager.loadArchive();
#else
    assetManager.loadRaw();
#endif
}

UVK::UVKGlobal::~UVKGlobal()
{
    delete currentLevel;
    delete instance;
}

void UVK::UVKGlobal::finalizeOpening()
{
    openFunction();

    openFunction = [=](){};
}

std::vector<UVK::InputAction>& UVK::UVKGlobal::getActions()
{
    return inputActionList;
}

bool& UVK::UVKGlobal::getEditor()
{
    return bEditor;
}

void UVK::UVKGlobal::openLevelInternal(UVK::String name)
{
    UVK::Level::openInternal(name);
}