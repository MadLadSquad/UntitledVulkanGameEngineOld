#include "Device.hpp"
#include "Swapchain.hpp"

void UVK::VKDevice::createDevice(Swapchain& swapchain) noexcept
{
    indices = createPhysicalDevice(swapchain);

    uint32_t queueFamilyCount = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyList.data());

    constexpr float priority = 1.0f;

    VkDeviceQueueCreateInfo createInfos[] =
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

    constexpr VkPhysicalDeviceFeatures deviceFeatures = {};

    const uint32_t queueInfoCount = indices.graphicsFamily == indices.presentationFamily ? 1 : 2;

    const VkDeviceCreateInfo deviceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = queueInfoCount,
        .pQueueCreateInfos = createInfos,
        .enabledExtensionCount = deviceExtensions.size(),
        .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures = &deviceFeatures
    };

    auto result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a logical device! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
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
        VkPhysicalDeviceProperties properties = {};
        vkGetPhysicalDeviceProperties(devices[i], &properties);

        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            bFoundDiscreteDevice = true;
        else
            continue;

        VkPhysicalDeviceMemoryProperties memoryProperties = {};
        vkGetPhysicalDeviceMemoryProperties(devices[i], &memoryProperties);

        auto* heaps = memoryProperties.memoryHeaps;
        uint64_t size = 0;
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

        vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &queueFamilyCount, queueFamilyList.data());

        int j = 0;
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

        if (!families.valid())
            continue;
skip_family_validity_check:
        vkEnumerateDeviceExtensionProperties(devices[i], nullptr, &extensionCount, nullptr);
        if (extensionCount == 0)
            continue;
        extensions.resize(extensionCount);
        vkEnumerateDeviceExtensionProperties(devices[i], nullptr, &extensionCount, extensions.data());

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
            if (!bHasExtension)
                goto continue_to_other_device_in_list;
        }

        if (!swapchain.getSwapchainDetails(devices[i], families))
            continue;

        if (size > largestMemorySize)
        {
            largestMemorySize = size;
            largestMemorySizeFoundIndex = i;
            lastSavedIndex = families;
        }
continue_to_other_device_in_list:;
    }

    if (!bFoundDiscreteDevice || largestMemorySizeFoundIndex == 0)
        physicalDevice = devices[0];
    else
        physicalDevice = devices[largestMemorySizeFoundIndex];

    VkPhysicalDeviceProperties physicalDeviceProperties = {};
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

    logger.consoleLog("Loaded Vulkan device ", UVK_LOG_TYPE_SUCCESS, physicalDeviceProperties.deviceName);
    return lastSavedIndex;
}

UVK::VKDevice::~VKDevice() noexcept
{
    destroyDevice();
}
