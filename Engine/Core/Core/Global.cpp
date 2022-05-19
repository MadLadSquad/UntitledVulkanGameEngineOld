#include "Global.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <UVKShaderCompiler/Src/Functions.hpp>
#ifdef _WIN32
    #include <windows.h>
#endif

UVK::UVKGlobal::UVKGlobal() noexcept
{
    // So you're wondering why this useless if statement exists, well my friend you have to hear this story I have for you.
    // It was the 5th of May 2022, while testing the engine on Windows I spotted a weird error. Usually the localeManager.openLocaleConfig() function
    // would print out a warning because the Config/Translations folder didn't exist. The weird thing was that this happened 2 times?? Ok so this wasn't a problem
    // I tought "It's probably because I implemented editor translations" - I said to myself. Turns out that wasn't the case. Later when I created a translation folder
    // the engine would crash on the destructor of the global, which was very unexpected to say the least. I debugged for a bit and turns out that the constructor and destructor got called
    // 2 times in a row??????? Maybe it's caused by our library configuation and this being a global but I can't be sure. Anyway this if statement is here
    // to prevent double initialization on Windows. For the destructor that you can see below we just hardcoded an ExitProcess(0) statement to the end of it so that the program closes
    // on the first call. I still don't know what this is and if you're reading this and might be able to help you can submit an issue to the UntitledVulkanGameEngine repository because
    // I don't know how this even works
    static bool bFirst = true;
    if (bFirst)
    {
        colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
        assetManager.load();
        localeManager.openLocaleConfig();
        // Set the UVKShaderCompiler path and check for recompilation
        USC::setPrefixDir("../");
        USC::checkForCompile();
        bFirst = false;
    }
}

UVK::UVKGlobal::~UVKGlobal() noexcept
{
    delete currentLevel;
    delete instance;
#ifdef _WIN32
    ExitProcess(0);
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