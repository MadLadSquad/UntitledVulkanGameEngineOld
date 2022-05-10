#include <GL/glew.h>
#include "CoreComponent.hpp"
#include "MeshComponentRaw.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include "Core/Actor.hpp"

void UVK::MeshComponentRaw::create(std::vector<VKVertex> vertices, std::vector<uint32_t> indices, VKDevice& dev, Commands& cmd, VKDescriptors& desc, const UVK::FString& textureLoc) noexcept
{
    device = &dev;
    commands = &cmd;
    descriptors = &desc;
    mesh = VKMesh(*device, device->getGraphicsQueue(), commands->getCommandPool(), std::move(vertices), std::move(indices));
    texture = Texture(textureLoc, *device, *commands, *descriptors);
    texture.load();
}

void UVK::MeshComponentRaw::update(size_t index, uint32_t currentImage, GraphicsPipeline& pipeline) noexcept
{
    mesh.model.model = glm::mat4(1.0);
    Math::translate(mesh.model.model, translation);
    Math::rotate(mesh.model.model, rotation);
    Math::scale(mesh.model.model, scale);

    VkBuffer vertexBuffers[] = { mesh.getVertexBuffer().getBuffer() };
    VkDescriptorSet descriptorSets[] = { descriptors->getDescriptorSets()[currentImage], descriptors->getSamplerDescriptorSets()[texture.getImage()] };
    VkDeviceSize offsets[] = { 0 };

    auto& cmd = commands->getCommandBuffers()[currentImage];
    vkCmdBindVertexBuffers(cmd, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(cmd, mesh.getIndexBuffer().getBuffer(), 0, VK_INDEX_TYPE_UINT32);

    //uint32_t dynamicOffset = static_cast<uint32_t>(modelUniformAlignment) * index;
    vkCmdPushConstants(cmd, pipeline.getPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, global.initInfo->shaderPushConstant.size, global.initInfo->shaderPushConstant.data);
    vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getPipelineLayout(), 0, 2, descriptorSets, 0, nullptr);

    vkCmdDrawIndexed(cmd, mesh.indexCount(), 1, 0, 0, 0);
}

void UVK::MeshComponentRaw::destroy() noexcept
{
    texture.destroy();
    mesh.destroyVertexBuffer();
}
