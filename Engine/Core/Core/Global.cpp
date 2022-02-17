// Global.cpp
// Last update 7/2/2022 by Madman10K
#include "Global.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#ifdef _WIN32
    #include <windows.h>
#endif

UVK::UVKGlobal::UVKGlobal()
{
    colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
    assetManager.load();
}

UVK::UVKGlobal::~UVKGlobal()
{
    delete currentLevel;
    delete instance;
#ifdef _WIN32
    //ExitProcess(0);
#endif
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

void UVK::UVKGlobal::openLevelInternal(UVK::String name, bool bfirst)
{
    UVK::Level::openInternal(name, bfirst);
}