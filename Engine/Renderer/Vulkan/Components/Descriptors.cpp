#include "Descriptors.hpp"
#include "Swapchain.hpp"
#include <Core/Global.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>

UVK::VKDescriptors::VKDescriptors(UVK::VKDevice& dev, Swapchain& swap, VKResources& res)
{
    device = &dev;
    swapchain = &swap;
    swapchain->descriptors = this;
    resources = &res;
}

void UVK::VKDescriptors::createDescriptorSetLayout() noexcept
{
    // Creates the bindings for the descriptor set layout, so it holds the data for the normal and dynamic uniform buffers
    constexpr VkDescriptorSetLayoutBinding layoutBindings[] =
    {
        {
            .binding = 0,
            .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount = 1,
            .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
            .pImmutableSamplers = nullptr,
        },
        {
            .binding = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
            .descriptorCount = 1,
            .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
            .pImmutableSamplers = nullptr
        }
    };
    uint8_t size = 1;
    // Change the size to include the dynamic uniform buffer part if the programmer is using dynamic uniform buffers
    if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
        size = 2;
    const VkDescriptorSetLayoutCreateInfo layoutCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = size,
        .pBindings = layoutBindings // Pass the bindings
    };

    // Create the layout
    auto result = vkCreateDescriptorSetLayout(device->getDevice(), &layoutCreateInfo, nullptr, &descriptorSetLayout);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't create a Vulkan descriptor set layout! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    // Create the binding for the sampler bindings
    constexpr VkDescriptorSetLayoutBinding samplerLayoutBindings
    {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,    // Here it needs to be combined
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
        .pImmutableSamplers = nullptr
    };

    const VkDescriptorSetLayoutCreateInfo samplerDescriptorSetCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &samplerLayoutBindings // Pass the sampler bindings
    };
    // Create the sampler bindings
    result = vkCreateDescriptorSetLayout(device->getDevice(), &samplerDescriptorSetCreateInfo, nullptr, &samplerSetLayout);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't create the sampler descriptor set layout! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

const VkDescriptorSetLayout& UVK::VKDescriptors::samplerLayout() const noexcept
{
    return samplerSetLayout;
}

void UVK::VKDescriptors::destroyDescriptorSetLayout() noexcept
{
    vkDestroyDescriptorSetLayout(device->getDevice(), descriptorSetLayout, nullptr);
}

const VkDescriptorSetLayout& UVK::VKDescriptors::layout() const noexcept
{
    return descriptorSetLayout;
}

void UVK::VKDescriptors::createDescriptorPool() noexcept
{
    // Set the sizes for the uniform and dynamic uniform buffers
    const VkDescriptorPoolSize poolSizes[] =
    {
        {
            .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount = static_cast<uint32_t>(resources->getUniformBuffers().size())
        },
        {
            .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
            .descriptorCount = static_cast<uint32_t>(resources->getDynamicUniformBuffers().size())
        }
    };

    uint8_t size = 1;
    // Set the size to include the dynamic uniform buffer if the programmer has defined one
    if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
        size = 2;

    const VkDescriptorPoolCreateInfo poolCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = static_cast<uint32_t>(resources->getUniformBuffers().size()),    // Create a set for every uniform buffer
        .poolSizeCount = size,
        .pPoolSizes = poolSizes
    };

    // Create the destriptor pool
    auto result = vkCreateDescriptorPool(device->getDevice(), &poolCreateInfo, nullptr, &descriptorPool);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't create a Vulkan descriptor pool! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    constexpr VkDescriptorPoolSize poolSize =
    {
        .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, // TODO: Remove this combined image sampler since it's not a good practice
        .descriptorCount = VK_MAX_OBJECTS, // TODO: Make it so textures can be changed for an object
    };

    // TODO: It's not good practice making it like this so yeah
    const VkDescriptorPoolCreateInfo samplerPoolCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = VK_MAX_OBJECTS,
        .poolSizeCount = 1,
        .pPoolSizes = &poolSize
    };
    result = vkCreateDescriptorPool(device->getDevice(), &samplerPoolCreateInfo, nullptr, &samplerDescriptorPool);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't create the texture sampler descriptor pool! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

void UVK::VKDescriptors::destroyDescriptorPool() noexcept
{
    vkDestroyDescriptorPool(device->getDevice(), descriptorPool, nullptr);
}

void UVK::VKDescriptors::createDescriptorSets() noexcept
{
    descriptorSets.resize(resources->getUniformBuffers().size());

    std::vector<VkDescriptorSetLayout> setLayouts(descriptorSets.size(), descriptorSetLayout);

    const VkDescriptorSetAllocateInfo descriptorSetAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = static_cast<uint32_t>(setLayouts.size()),
        .pSetLayouts = setLayouts.data(),
    };

    const auto result = vkAllocateDescriptorSets(device->getDevice(), &descriptorSetAllocateInfo, descriptorSets.data());
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't allocate vulkan descriptor sets! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    uint8_t size = 1;
    // Set the size variable to include dynamic uniform buffers
    if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
        size = 2;
    for (size_t i = 0; i < resources->getUniformBuffers().size(); i++)
    {
        VkDescriptorBufferInfo descriptorBufferInfos[2] =
        {
            {
                .buffer = resources->getUniformBuffers()[i].getBuffer(),        // The uniform buffer
                .offset = 0,
                .range = global.instance->initInfo.shaderConstantStruct.size    // Basically the size of the struct
            },
        };
        if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
        {
            descriptorBufferInfos[1] =
            {
                .buffer = resources->getDynamicUniformBuffers()[i].getBuffer(),     // The dynamic uniform buffer
                .offset = 0,
                .range = resources->getModelUniformAlignment()                      // The size of the dynamic uniform buffer
            };
        }

        const VkWriteDescriptorSet descriptorWrites[] =
        {
            {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .dstSet = descriptorSets[i],
                .dstBinding = 0,
                .dstArrayElement = 0,
                .descriptorCount = 1,
                .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                .pBufferInfo = &descriptorBufferInfos[0]
            },
            {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .dstSet = descriptorSets[i],
                .dstBinding = 1,
                .dstArrayElement = 0,
                .descriptorCount = 1,
                .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
                .pBufferInfo = &descriptorBufferInfos[1]
            }
        };

        // Update the sets
        vkUpdateDescriptorSets(device->getDevice(), size, descriptorWrites, 0, nullptr);
    }
}

void UVK::VKDescriptors::destroyDescriptorSets() noexcept
{
    vkFreeDescriptorSets(device->getDevice(), descriptorPool, descriptorSets.size(), descriptorSets.data());
}

void UVK::VKDescriptors::createPushConstantRange() noexcept
{
    // Define the push constants
    pushConstantRange =
    {
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        .offset = 0,
        .size = global.instance->initInfo.shaderPushConstant.size,
    };
}


const std::vector<VkDescriptorSet>& UVK::VKDescriptors::getDescriptorSets() const noexcept
{
    return descriptorSets;
}

VkDescriptorPool& UVK::VKDescriptors::getPool() noexcept
{
    return descriptorPool;
}

size_t UVK::VKDescriptors::createTextureDescriptor(VkImageView imageView, const VkSampler& textureSampler) noexcept
{
    VkDescriptorSet descriptorSet = {};
    const VkDescriptorSetAllocateInfo descriptorSetAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = samplerDescriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &samplerSetLayout,
    };

    auto result = vkAllocateDescriptorSets(device->getDevice(), &descriptorSetAllocateInfo, &descriptorSet);
    if (result != VK_SUCCESS)
    {
        Logger::log("Failed to allocate the sampler descriptor set! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    const VkDescriptorImageInfo imageInfo =
    {
        .sampler = textureSampler,
        .imageView = imageView,
        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
    };

    const VkWriteDescriptorSet descriptorSetWrite =
    {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = descriptorSet,
        .dstBinding = 0,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .pImageInfo = &imageInfo
    };
    vkUpdateDescriptorSets(device->getDevice(), 1, &descriptorSetWrite, 0, nullptr);
    samplerDescriptorSets.push_back(descriptorSet);
    return samplerDescriptorSets.size() - 1;
}

void UVK::VKDescriptors::destroyTextureDescriptor()
{
    vkDestroyDescriptorPool(device->getDevice(), samplerDescriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(device->getDevice(), samplerSetLayout, nullptr);
}

const std::vector<VkDescriptorSet>& UVK::VKDescriptors::getSamplerDescriptorSets() const noexcept
{
    return samplerDescriptorSets;
}

const VkPushConstantRange& UVK::VKDescriptors::getPushConstantRange() const noexcept
{
    return pushConstantRange;
}
