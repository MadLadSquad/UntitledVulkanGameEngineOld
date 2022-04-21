#include "Global.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#ifdef _WIN32
    #include <windows.h>
#endif

UVK::UVKGlobal::UVKGlobal() noexcept
{
    colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
    assetManager.load();
    localeManager.openLocaleConfig();
}

UVK::UVKGlobal::~UVKGlobal() noexcept
{
    delete currentLevel;
    delete instance;
#ifdef _WIN32
    //ExitProcess(0);
#endif
}

void UVK::UVKGlobal::finalizeOpening() noexcept
{
    openFunction();

    openFunction = [=](){};
}

std::vector<UVK::InputAction>& UVK::UVKGlobal::getActions() noexcept
{
    return inputActionList;
}

bool& UVK::UVKGlobal::getEditor() noexcept
{
    return bEditor;
}

void UVK::UVKGlobal::openLevelInternal(UVK::String name, bool bfirst) noexcept
{
    UVK::Level::openInternal(name, bfirst);
}