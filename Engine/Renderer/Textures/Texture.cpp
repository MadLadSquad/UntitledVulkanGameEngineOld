#define STB_IMAGE_IMPLEMENTATION
#include <vulkan/vulkan.h>
#include "Texture.hpp"
#include <stb/stb_image.h>
#include <Renderer/Vulkan/Components/Buffer.hpp>
#include <Renderer/Vulkan/Components/Commands.hpp>
#include <Renderer/Vulkan/Components/Swapchain.hpp>
#include <Renderer/Vulkan/Components/Descriptors.hpp>

void UVK::Texture::load() noexcept
{
    auto img = gen();
    VKBuffer stagingBuffer;
    stagingBuffer.create(*device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    void* data;
    vkMapMemory(device->getDevice(), stagingBuffer.getMemory(), 0, size, 0, &data);
    memcpy(data, img, size);
    vkUnmapMemory(device->getDevice(), stagingBuffer.getMemory());

    stbi_image_free(img);

    ///mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(width, height))) + 1);
    image.createImage({ width, height }, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, imageMemory, *device, mipLevels);
    stagingBuffer.transitionImageLayout(device->getGraphicsQueue(), commands->getCommandPool(), image.image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
    stagingBuffer.copyImageBuffer(device->getGraphicsQueue(), commands->getCommandPool(), image.image, { width, height });
    //generateMipMaps();

    stagingBuffer.transitionImageLayout(device->getGraphicsQueue(), commands->getCommandPool(), image.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, mipLevels);
    stagingBuffer.destroy();

    image.imageView = UVK::Swapchain::createImageView(image.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, *device, mipLevels);

    const VkSamplerCustomBorderColorCreateInfoEXT customBorderColorCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT,
        .customBorderColor =
        {
            .float32 =
            {
                settings.borderColour.x,
                settings.borderColour.y,
                settings.borderColour.z,
                settings.borderColour.w,
            }
        },
        .format = VK_FORMAT_R8G8B8A8_UNORM,
    };

    const VkSamplerCreateInfo samplerCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .pNext = &customBorderColorCreateInfo,
        .magFilter = static_cast<VkFilter>(settings.magFilter),      // Add this as a setting in the renderer per texture
        .minFilter = static_cast<VkFilter>(settings.minFilter),
        .mipmapMode = static_cast<VkSamplerMipmapMode>(settings.mipMapMode),
        .addressModeU = static_cast<VkSamplerAddressMode>(settings.wrapModes[0]),
        .addressModeV = static_cast<VkSamplerAddressMode>(settings.wrapModes[1]),
        .addressModeW = static_cast<VkSamplerAddressMode>(settings.wrapModes[2]),
        .mipLodBias = 0.0f,
        .anisotropyEnable = VK_TRUE,
        .maxAnisotropy = 16,
        .minLod = 0.0f,
        .maxLod = static_cast<float>(mipLevels),
        .borderColor = VK_BORDER_COLOR_FLOAT_CUSTOM_EXT,
        .unnormalizedCoordinates = VK_FALSE,
    };
    const auto result = vkCreateSampler(device->getDevice(), &samplerCreateInfo, nullptr, &textureSampler);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a texture sampler! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    descriptorLocation = descriptors->createTextureDescriptor(image.imageView, textureSampler);
}

void UVK::Texture::loadImgui() noexcept
{

}

void UVK::Texture::destroy() noexcept
{
    vkDestroySampler(device->getDevice(), textureSampler, nullptr);
    vkDestroyImageView(device->getDevice(), image.imageView, nullptr);
    vkDestroyImage(device->getDevice(), image.image, nullptr);
    vkFreeMemory(device->getDevice(), imageMemory, nullptr);
    width = 0;
    height = 0;
}

void UVK::Texture::useTexture() const noexcept
{

}

unsigned char* UVK::Texture::gen() noexcept
{
    unsigned char* img = stbi_load(location.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (img == nullptr)
    {
        logger.consoleLog("Failed to load image file at location: ", UVK_LOG_TYPE_ERROR, location);
        std::terminate();
    }
    size = width * height * 4;

    return img;
}

UVK::Texture::Texture(const std::string& loc, VKDevice& dev, Commands& cmd, VKDescriptors& desc, TextureSettings sett)
{
    location = loc;
    device = &dev;
    commands = &cmd;
    descriptors = &desc;
    settings = sett;
}

UVK::Texture::Texture(const std::string &loc)
{

}

void UVK::Texture::generateMipMaps()
{
    auto commandBuffer = VKBuffer::beginCommandBuffer(commands->getCommandPool(), *device);

    VkImageMemoryBarrier barrier =
    {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = image.image,
        .subresourceRange =
        {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1,
        }
    };

    auto mipWidth = width;
    auto mipHeight = height;
    for (uint32_t i = 0; i < mipLevels; i++)
    {
        barrier.subresourceRange.baseMipLevel = i - 1;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

        vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

        const VkImageBlit blit
        {
            .srcSubresource =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .mipLevel = i - 1,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
            .srcOffsets =
            {
                { 0, 0, 0 },
                { mipWidth, mipHeight, 1 },
            },
            .dstSubresource =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .mipLevel = i,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
            .dstOffsets =
            {
                { 0, 0, 0 },
                { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 },
            }
        };
        vkCmdBlitImage(commandBuffer, image.image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &blit, static_cast<VkFilter>(settings.mipMapMode));
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

        if (mipWidth > 1) mipWidth /= 2;
        if (mipHeight > 1) mipHeight /= 2;
    }
    barrier.subresourceRange.baseMipLevel = mipLevels - 1;
    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

    VKBuffer::endCommandBuffer(device->getGraphicsQueue(), commands->getCommandPool(), commandBuffer, *device);
}
