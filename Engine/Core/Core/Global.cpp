// Global.cpp
// Last update 2/9/2021 by Madman10K
#include "Global.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>

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

std::vector<UVK::InputAction>& UVK::InputActions::getActions()
{
    return global.getActions();
}

void UVK::Math::translate(glm::mat4& mat, UVK::FVector vt)
{
    if (global.bUsesVulkan)
    {
        mat = glm::translate(mat, FVector(vt.x, -vt.y, vt.z));
    }
    else
    {
        mat = glm::translate(mat, vt);
    }
}

void UVK::Math::rotate(glm::mat4& mat, UVK::FVector vt)
{
    if (global.bUsesVulkan)
    {
        auto rot = glm::toMat4(glm::quat(FVector(vt.x, -vt.y, vt.z)));
        mat *= rot;
    }
    else
    {
        auto rot = glm::toMat4(glm::quat(vt));
        mat *= rot;
    }
}

void UVK::Math::scale(glm::mat4& mat, UVK::FVector vt)
{
    if (global.bUsesVulkan)
    {
        mat = glm::scale(mat, FVector(vt.x, -vt.y, vt.z));
    }
    else
    {
        mat = glm::scale(mat, vt);
    }
}

bool& UVK::UVKGlobal::getEditor()
{
    return bEditor;
}

void UVK::UVKGlobal::openLevelInternal(UVK::String name)
{
    UVK::Level::openInternal(name);
}