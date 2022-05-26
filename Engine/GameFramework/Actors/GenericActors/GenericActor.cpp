#include "GenericActor.hpp"
#include <GameFramework/Components/Components/MeshComponent.hpp>
#include <Renderer/Vulkan/VulkanRenderer.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>

void UVK::GenericActor::createMesh(const UVK::FString& path) noexcept
{
    static size_t i = 0;
    Actor actor("GenericMeshActor", i, path);
    auto& mcomp = actor.add<UVK::MeshComponent>();
    mcomp.create(path.c_str(), global.renderer->device, global.renderer->commands, global.renderer->descriptors, actor.get<CoreComponent>());
    i++;
}
