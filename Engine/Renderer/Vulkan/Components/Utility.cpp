#include "Utility.hpp"
#include <UVKShaderCompiler/Src/Functions.hpp>
#include "Device.hpp"

bool UVK::QueueFamilyIndices::valid() const noexcept
{
    return graphicsFamily >= 0 && presentationFamily >= 0;
}

std::vector<char> UVK::VKShader::getShaderBytecode() const noexcept
{
    auto hash = USC::getShaderHash(name.c_str());
    bool bFound = false;
    for (const auto& a : std_filesystem::directory_iterator("../Generated"))
    {
        if (!a.is_directory())
        {
            if (a.path() == std_filesystem::path("../Generated/" + hash + ".spv"))
            {
                bFound = true;
                break;
            }
        }
    }

    if (!bFound)
        USC::recompileShaders();

    std::ifstream in("../Generated/" + hash + ".spv", std::ios::ate | std::ios::binary);
    if (!in.is_open())
    {
        logger.consoleLog("Failed to load file!", UVK_LOG_TYPE_ERROR);
        std::terminate();
    }

    std::vector<char> returnVal(in.tellg());
    in.seekg(0);
    in.read(returnVal.data(), returnVal.size());
    in.close();

    return returnVal;
}

UVK::VKShader::VKShader(const char* fname) noexcept
{
    init(fname);
}

void UVK::VKShader::init(const char* fname) noexcept
{
    name = fname;
    if (name.ends_with(".vert"))
        type = VKShaderType::VK_SHADER_TYPE_VERTEX;
    else if (name.ends_with(".frag"))
        type = VKShaderType::VK_SHADER_TYPE_FRAGMENT;
    else if (name.ends_with(".geom"))
        type = VKShaderType::VK_SHADER_TYPE_GEOMETRY;
    else if (name.ends_with(".comp"))
        type = VKShaderType::VK_SHADER_TYPE_COMPUTE;
    else if (name.ends_with(".tesc"))
        type = VKShaderType::VK_SHADER_TYPE_TESSELLATION_CONTROL;
    else if (name.ends_with(".tese"))
        type = VKShaderType::VK_SHADER_TYPE_TESSELLATION_EVALUATION;
    else
        type = VKShaderType::VK_SHADER_TYPE_NONE;
}

void UVK::VKShader::each(const std::function<void(VKShader&)>& func) noexcept
{
    for (auto& a : std_filesystem::recursive_directory_iterator("../Content/"))
    {
        if (!a.is_directory())
        {
            VKShader shader(a.path().string().c_str());
            if (shader.type == VKShaderType::VK_SHADER_TYPE_NONE)
                continue;
            func(shader);
        }
    }
}

void UVK::SwapchainImage::createImage(const UVK::FVector2& size, const VkFormat& format, const VkImageTiling& tiling, const VkImageUsageFlags& usageFlags, const VkMemoryPropertyFlags& propertyFlags, VkDeviceMemory& memory, VKDevice& device, uint32_t mipLevels)
{
    const VkImageCreateInfo imageCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = format,
        .extent =
        {
            .width = static_cast<uint32_t>(size.x),
            .height = static_cast<uint32_t>(size.y),
            .depth = 1
        },
        .mipLevels = mipLevels,
        .arrayLayers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = tiling,
        .usage = usageFlags,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    };
    auto result = vkCreateImage(device.getDevice(), &imageCreateInfo, nullptr, &image);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a vulkan image! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    VkMemoryRequirements memoryRequirements = {};
    vkGetImageMemoryRequirements(device.getDevice(), image, &memoryRequirements);

    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(device.getPhysicalDevice(), &memoryProperties);

    uint32_t i = 0;
    for (; i < memoryProperties.memoryTypeCount; i++)
        if ((memoryRequirements.memoryTypeBits & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & propertyFlags) == propertyFlags)
            goto success;
    logger.consoleLog("Couldn't get required memory property flags from the currently selected device!", UVK_LOG_TYPE_ERROR);
    std::terminate();
success:
    const VkMemoryAllocateInfo memoryAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = i
    };

    result = vkAllocateMemory(device.getDevice(), &memoryAllocateInfo, nullptr, &memory);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't allocate memory for hte given image! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    vkBindImageMemory(device.getDevice(), image, memory, 0);
}

VkFormat UVK::SwapchainImage::findBestImageFormat(const std::vector<VkFormat>& formats, const VkImageTiling& tiling, VkFormatFeatureFlags featureFlags, VKDevice& device)
{
    for (auto& a : formats)
    {
        VkFormatProperties properties;
        vkGetPhysicalDeviceFormatProperties(device.getPhysicalDevice(), a, &properties);
        if ((tiling == VK_IMAGE_TILING_LINEAR && (properties.linearTilingFeatures & featureFlags) == featureFlags) || (tiling == VK_IMAGE_TILING_OPTIMAL && (properties.optimalTilingFeatures & featureFlags) == featureFlags))
            return a;
    }
    logger.consoleLog("Couldn't find optimal image format!", UVK_LOG_TYPE_ERROR);
    std::terminate();
}
