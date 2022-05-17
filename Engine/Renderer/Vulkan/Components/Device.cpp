#include "Device.hpp"
#include "Swapchain.hpp"
#include <Renderer/Renderer.hpp>

void UVK::VKDevice::createDevice(Swapchain& swapchain) noexcept
{
    indices = createPhysicalDevice(swapchain);

    uint32_t queueFamilyCount = 0;

    // Get the queue family properties for the given physical device
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyList.data());

    constexpr float priority = 1.0f;

    // Create the queues given the indices
    const VkDeviceQueueCreateInfo createInfos[] =
    {
        {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = static_cast<uint32_t>(indices.graphicsFamily),
            .queueCount = 1,
            .pQueuePriorities = &priority
        },
        {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = static_cast<uint32_t>(indices.presentationFamily),
            .queueCount = 1,
            .pQueuePriorities = &priority
        }
    };

    // Set sample rate shading to true or false depending on the setting
    VkBool32 sampleRateShading = Renderer::sampleRateShading() ? VK_TRUE : VK_FALSE;

    // Enable physical device features
    const VkPhysicalDeviceFeatures deviceFeatures =
    {
        .sampleRateShading = sampleRateShading,
        .samplerAnisotropy = VK_TRUE,           // We're using Anisotropy
    };
    constexpr VkPhysicalDeviceCustomBorderColorFeaturesEXT physicalDeviceCustomBorderColorFeaturesExt
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT,
        .customBorderColors = VK_TRUE,                                                  // Enable custom texture border colours
        .customBorderColorWithoutFormat = VK_FALSE,                                     // Require format for the custom border colours
    };

    const uint32_t queueInfoCount = indices.graphicsFamily == indices.presentationFamily ? 1 : 2;

    const VkDeviceCreateInfo deviceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &physicalDeviceCustomBorderColorFeaturesExt,   // Set the pNext pointer to point to the custom border colours struct
        .queueCreateInfoCount = queueInfoCount,
        .pQueueCreateInfos = createInfos,
        .enabledExtensionCount = deviceExtensions.size(),
        .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures = &deviceFeatures
    };

    // Create the logical device
    auto result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a logical device! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    // Get the queues
    vkGetDeviceQueue(device, indices.graphicsFamily, 0, &queue);
    vkGetDeviceQueue(device, indices.presentationFamily, 0, &presentationQueue);
}

void UVK::VKDevice::destroyDevice() noexcept
{
    vkDestroyDevice(device, nullptr);
}

VkDevice& UVK::VKDevice::getDevice() noexcept
{
    return device;
}

UVK::VKDevice::VKDevice(UVK::VKInstance& instance) noexcept
{
    this->instance = &instance;
}

UVK::QueueFamilyIndices UVK::VKDevice::createPhysicalDevice(Swapchain& swapchain) noexcept
{
    uint32_t deviceCount;
    // Get the list of physical devices
    vkEnumeratePhysicalDevices(instance->data(), &deviceCount, nullptr);
    if (deviceCount == 0)
    {
        logger.consoleLog("Could not find any graphics devices on this system!", UVK_LOG_TYPE_ERROR);
        std::terminate();
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance->data(), &deviceCount, devices.data());

    bool bFoundDiscreteDevice = false;
    uint32_t largestMemorySizeFoundIndex = 0;
    uint64_t largestMemorySize = 0;
    QueueFamilyIndices lastSavedIndex = {};

    for (size_t i = 0; i < devices.size(); i++)
    {
        // Get the properties of the device
        VkPhysicalDeviceProperties properties = {};
        vkGetPhysicalDeviceProperties(devices[i], &properties);

        // If it is not discrete skip this iteration
        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            bFoundDiscreteDevice = true;
        else
            continue;

        VkPhysicalDeviceMemoryProperties memoryProperties = {};
        vkGetPhysicalDeviceMemoryProperties(devices[i], &memoryProperties);

        auto* heaps = memoryProperties.memoryHeaps;
        uint64_t size = 0;
        // Set the size of the memory for the given GPU
        for (size_t j = 0; j < memoryProperties.memoryHeapCount; j++)
        {
            if (heaps[j].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
            {
                size += heaps->size;
                goto exit_embedded_loop;
            }
        }
exit_embedded_loop:

        QueueFamilyIndices families = {};
        uint32_t queueFamilyCount = 0;
        uint32_t extensionCount = 0;
        std::vector<VkExtensionProperties> extensions;

        // Get the queue families
        vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &queueFamilyCount, queueFamilyList.data());

        int j = 0;
        // Select the queue family
        for (; j < queueFamilyList.size(); j++)
        {
            const auto& a = queueFamilyList[j];
            if (a.queueCount > 0 && a.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                families.graphicsFamily = j;
                VkBool32 bSupportsPresentation = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(devices[i], j, swapchain.surface, &bSupportsPresentation);

                if (bSupportsPresentation)
                    families.presentationFamily = j;
                goto skip_family_validity_check;
            }
        }

        // If invalid skip
        if (!families.valid())
            continue;
skip_family_validity_check:
        // Get the list of device extensions
        vkEnumerateDeviceExtensionProperties(devices[i], nullptr, &extensionCount, nullptr);
        if (extensionCount == 0)
            continue;
        extensions.resize(extensionCount);
        vkEnumerateDeviceExtensionProperties(devices[i], nullptr, &extensionCount, extensions.data());

        // Iterate the list and make sure the device supports all
        for (const auto& a : deviceExtensions)
        {
            bool bHasExtension = false;
            for (const auto& f : extensions)
            {
                if (strcmp(a, f.extensionName) == 0)
                {
                    bHasExtension = true;
                    goto breakout;
                }
            }
breakout:
            // If it doesn't have the extension, skip
            if (!bHasExtension)
                goto continue_to_other_device_in_list;
        }

        if (!swapchain.getSwapchainDetails(devices[i], families))
            continue;

        // If the size is larger set the index of the device to this since it's the best one so far
        if (size > largestMemorySize)
        {
            largestMemorySize = size;
            largestMemorySizeFoundIndex = i;
            lastSavedIndex = families;
        }
continue_to_other_device_in_list:;
    }

    // Set device[0] if we couldn't find it lol
    if (!bFoundDiscreteDevice || largestMemorySizeFoundIndex == 0)
        physicalDevice = devices[0];
    else
        physicalDevice = devices[largestMemorySizeFoundIndex];

    // Set the device properties variable real quick
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    setMSAASamples();
    logger.consoleLog("Loaded Vulkan device ", UVK_LOG_TYPE_SUCCESS, deviceProperties.deviceName);
    return lastSavedIndex;
}

VkQueue& UVK::VKDevice::getGraphicsQueue() noexcept
{
    return queue;
}

UVK::QueueFamilyIndices &UVK::VKDevice::getIndices() noexcept
{
    return indices;
}

VkQueue& UVK::VKDevice::getPresentationQueue() noexcept
{
    return presentationQueue;
}

VkPhysicalDevice& UVK::VKDevice::getPhysicalDevice() noexcept
{
    return physicalDevice;
}

void UVK::VKDevice::setMSAASamples() const noexcept
{
    // Set the MSAA sample level given the hardware supports it and is defined in the config file
    const VkSampleCountFlags counts = deviceProperties.limits.framebufferColorSampleCounts & deviceProperties.limits.framebufferDepthSampleCounts;
    if ((counts & VK_SAMPLE_COUNT_64_BIT) && UVK::Renderer::msaaSampleCount() > 32)
        UVK::Renderer::msaaSampleCount() = VK_SAMPLE_COUNT_64_BIT;
    else if ((counts & VK_SAMPLE_COUNT_32_BIT) && UVK::Renderer::msaaSampleCount() > 16)
        UVK::Renderer::msaaSampleCount() = VK_SAMPLE_COUNT_32_BIT;
    else if ((counts & VK_SAMPLE_COUNT_16_BIT) && UVK::Renderer::msaaSampleCount() > 8)
        UVK::Renderer::msaaSampleCount() = VK_SAMPLE_COUNT_16_BIT;
    else if ((counts & VK_SAMPLE_COUNT_8_BIT) && UVK::Renderer::msaaSampleCount() > 4)
        UVK::Renderer::msaaSampleCount() = VK_SAMPLE_COUNT_8_BIT;
    else if ((counts & VK_SAMPLE_COUNT_4_BIT) && UVK::Renderer::msaaSampleCount() > 2)
        UVK::Renderer::msaaSampleCount() = VK_SAMPLE_COUNT_4_BIT;
    else if ((counts & VK_SAMPLE_COUNT_2_BIT) && UVK::Renderer::msaaSampleCount() > 1)
        UVK::Renderer::msaaSampleCount() = VK_SAMPLE_COUNT_2_BIT;
    else if ((counts & VK_SAMPLE_COUNT_1_BIT) && UVK::Renderer::msaaSampleCount() >= 0)
        UVK::Renderer::msaaSampleCount() = VK_SAMPLE_COUNT_1_BIT;
}
