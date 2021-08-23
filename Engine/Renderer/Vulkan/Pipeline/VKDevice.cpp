// VKDevice.cpp
// Last update 16/8/2021 by Madman10K
#include "VKDevice.hpp"
#include <Core.hpp>
#ifndef __APPLE__
void UVK::Device::getPhysicalDevice()
{
    uint32_t deviceCount = 0;

    vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);

    // if the device doesn't support vulkan or no devices
    if (deviceCount == 0)
    {
        logger.consoleLog("Couldn't find any devices or any that support Vulkan!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    std::vector<VkPhysicalDevice> deviceList(deviceCount);
    vkEnumeratePhysicalDevices(*instance, &deviceCount, deviceList.data());

    device.physicalDevice = deviceList[0];

    for (const auto& device1 : deviceList)
    {
        if (checkDeviceSuitability(device1))
        {
            device.physicalDevice = device1;
            break;
        }
    }
}

void UVK::Device::createLogicalDevice()
{
    constexpr float priority = 1.0f;
    const VKQueueFamilyLocation location = getQueueFamilies();

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfoArr;
    std::set<int> queueFamilyIndices = { location.graphicsFamily, location.presentationFamily };

    for (auto& i : queueFamilyIndices)
    {
        queueCreateInfoArr.push_back
        (
            {
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                .queueFamilyIndex = static_cast<uint32_t>(i),
                .queueCount = 1,
                .pQueuePriorities = &priority
            }
        );
    }

    constexpr VkPhysicalDeviceFeatures deviceFeatures = {};
    const VkDeviceCreateInfo deviceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfoArr.size()),
        .pQueueCreateInfos = queueCreateInfoArr.data(),
        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
        .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures = &deviceFeatures,
    };

    if (vkCreateDevice(device.physicalDevice, &deviceCreateInfo, nullptr, &device.logicalDevice) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan logical device", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    // get global class access to queue
    vkGetDeviceQueue(device.logicalDevice, location.graphicsFamily, 0, &queue);
    vkGetDeviceQueue(device.logicalDevice, location.presentationFamily, 0, &presentationQueue);
}

void UVK::Device::destroyLogicalDevice() const
{
    vkDestroyDevice(device.logicalDevice, nullptr);
}

UVK::VKDevice& UVK::Device::getDevice()
{
    return device;
}

void UVK::Device::set(VkInstance* inst, VKSwapchain* swap)
{
    instance = inst;
    swapchain = swap;

    getPhysicalDevice();
    createLogicalDevice();
}

bool UVK::Device::checkDeviceSuitability(const VkPhysicalDevice& physicalDevice)
{
    // Check for properties
    VkPhysicalDeviceProperties deviceProperties = {};
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

    // Check for features
    VkPhysicalDeviceFeatures deviceFeatures = {};
    vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

    const VKQueueFamilyLocation location = getQueueFamilies();
    bool bExtensionsSupported = checkDeviceExtensionSupport();
    bool bSwapChainValid;

    const VKSwapchainSettings swapchainSettings = swapchain->getSwapchainSettings();
    bSwapChainValid = !swapchainSettings.presentationModes.empty() && !swapchainSettings.formats.empty();

    return location.isValid() && bExtensionsSupported && bSwapChainValid;
}

UVK::VKQueueFamilyLocation UVK::Device::getQueueFamilies() const
{
    VKQueueFamilyLocation familyLocation;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device.physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyPropertyList(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device.physicalDevice, &queueFamilyCount, queueFamilyPropertyList.data());

    // check for required type of queue
    for (int i = 0; i < queueFamilyPropertyList.size(); i++)
    {
        if (queueFamilyPropertyList[i].queueCount > 0 && queueFamilyPropertyList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            familyLocation.graphicsFamily = i;
        }

        VkBool32 presentationSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device.physicalDevice, i, swapchain->getSurface(), &presentationSupport);

        if (queueFamilyPropertyList[i].queueCount > 0 && presentationSupport)
        {
            familyLocation.presentationFamily = i;
        }

        if (familyLocation.isValid())
        {
            break;
        }
    }
    return familyLocation;
}

bool UVK::Device::checkDeviceExtensionSupport() const
{
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(device.physicalDevice, nullptr, &extensionCount, nullptr);

    if (extensionCount == 0)
    {
        return false;
    }

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device.physicalDevice, nullptr, &extensionCount, extensions.data());

    for (const auto& extension : deviceExtensions)
    {
        bool bExtension = false;

        for (const auto& ext : extensions)
        {
            if (strcmp(extension, ext.extensionName) == 0)
            {
                bExtension = true;
                break;
            }
        }

        if (!bExtension)
        {
            return false;
        }
    }

    return true;
}
#endif
