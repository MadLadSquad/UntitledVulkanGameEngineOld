// Device.cpp
// Last update 21/12/2021 by Madman10K
#include "Device.hpp"


void UVK::VKDevice::createDevice()
{
    auto families = createPhysicalDevice();

    uint32_t queueFamilyCount = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyList.data());

    constexpr float priority = 1.0f;
    const VkDeviceQueueCreateInfo queueCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = static_cast<uint32_t>(families.graphicsFamily),
        .queueCount = 1,
        .pQueuePriorities = &priority,
    };

    constexpr VkPhysicalDeviceFeatures deviceFeatures = {};

    const VkDeviceCreateInfo deviceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCreateInfo,
        .enabledExtensionCount = 0,
        .ppEnabledExtensionNames = nullptr,
        .pEnabledFeatures = &deviceFeatures
    };

    auto result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a logical device!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
    VkQueue queue;
    vkGetDeviceQueue(device, families.graphicsFamily, 0, &queue);
}

void UVK::VKDevice::destroyDevice()
{
    vkDestroyDevice(device, nullptr);
}

VkDevice& UVK::VKDevice::getDevice()
{
    return device;
}

VkPhysicalDevice& UVK::VKDevice::getPhysicalDevice()
{
    return physicalDevice;
}

UVK::VKDevice::VKDevice(UVK::VKInstance& instance)
{
    this->instance = &instance;
}

UVK::QueueFamilyIndices UVK::VKDevice::createPhysicalDevice()
{
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(instance->data(), &deviceCount, nullptr);
    if (deviceCount == 0)
    {
        logger.consoleLog("Could not find any graphics devices on this system!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
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
                goto skip_family_validity_check;
            }
        }

        if (!families.valid())
            continue;
skip_family_validity_check:
        if (size > largestMemorySize)
        {
            largestMemorySize = size;
            largestMemorySizeFoundIndex = i;
            lastSavedIndex = families;
        }
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
