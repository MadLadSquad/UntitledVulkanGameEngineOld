#include "Descriptors.hpp"
#include "Swapchain.hpp"

UVK::VKDescriptors::VKDescriptors(UVK::VKDevice& dev, Swapchain& swap, VKResources& res)
{
    device = &dev;
    swapchain = &swap;
    swapchain->descriptors = this;
    resources = &res;
}

void UVK::VKDescriptors::createDescriptorSetLayout() noexcept
{
    constexpr VkDescriptorSetLayoutBinding layoutBindings[] =
    {
        {
            .binding = 0,
            .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount = 1,
            .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
            .pImmutableSamplers = nullptr,
        },
        //{
        //    .binding = 1,
        //    .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        //    .descriptorCount = 1,
        //    .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        //    .pImmutableSamplers = nullptr
        //}
    };

    const VkDescriptorSetLayoutCreateInfo layoutCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = layoutBindings
    };

    auto result = vkCreateDescriptorSetLayout(device->getDevice(), &layoutCreateInfo, nullptr, &descriptorSetLayout);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a Vulkan descriptor set layout! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    constexpr VkDescriptorSetLayoutBinding samplerLayoutBindings
    {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
        .pImmutableSamplers = nullptr
    };

    const VkDescriptorSetLayoutCreateInfo samplerDescriptorSetCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &samplerLayoutBindings
    };
    result = vkCreateDescriptorSetLayout(device->getDevice(), &samplerDescriptorSetCreateInfo, nullptr, &samplerSetLayout);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create the sampler descriptor set layout! Error code: ", UVK_LOG_TYPE_ERROR, result);
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
    const VkDescriptorPoolSize poolSizes[] =
    {
        {
            .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount = static_cast<uint32_t>(resources->getUniformBuffers().size())
        },
        //{
        //    .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        //    .descriptorCount = static_cast<uint32_t>(swapchain->dynamicUniformBuffers.size())
        //}
    };

    const VkDescriptorPoolCreateInfo poolCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = static_cast<uint32_t>(resources->getUniformBuffers().size()),
        .poolSizeCount = 1,
        .pPoolSizes = poolSizes
    };

    auto result = vkCreateDescriptorPool(device->getDevice(), &poolCreateInfo, nullptr, &descriptorPool);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a Vulkan descriptor pool! Error code: ", UVK_LOG_TYPE_ERROR, result);
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
        logger.consoleLog("Couldn't create the texture sampler descriptor pool! Error code: ", UVK_LOG_TYPE_ERROR, result);
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
        logger.consoleLog("Couldn't allocate vulkan descriptor sets! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    for (size_t i = 0; i < resources->getUniformBuffers().size(); i++)
    {
        const VkDescriptorBufferInfo descriptorBufferInfos[] =
        {
            {
                .buffer = resources->getUniformBuffers()[i].getBuffer(),
                .offset = 0,
                .range = sizeof(VP)
            },
            //{
            //    .buffer = swapchain->dynamicUniformBuffers[i].getBuffer(),
            //    .offset = 0,
            //    .range = swapchain->modelUniformAlignment
            //}
        };

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
            //{
            //    .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            //    .dstSet = descriptorSets[i],
            //    .dstBinding = 1,
            //    .dstArrayElement = 0,
            //    .descriptorCount = 1,
            //    .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
            //    .pBufferInfo = &descriptorBufferInfos[1]
            //}
        };

        vkUpdateDescriptorSets(device->getDevice(), 1, descriptorWrites, 0, nullptr);
    }
}

void UVK::VKDescriptors::destroyDescriptorSets() noexcept
{
    vkFreeDescriptorSets(device->getDevice(), descriptorPool, descriptorSets.size(), descriptorSets.data());
}

void UVK::VKDescriptors::createPushConstantRange() noexcept
{

}

void UVK::VKDescriptors::destroyPushConstantRange() noexcept
{

}

const VkPushConstantRange& UVK::VKDescriptors::getPushConstantRange() const noexcept
{
    return pushConstantRange;
}

const std::vector<VkDescriptorSet> &UVK::VKDescriptors::getDescriptorSets() const noexcept
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
        logger.consoleLog("Failed to allocate the sampler descriptor set! Error code: ", UVK_LOG_TYPE_ERROR, result);
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
