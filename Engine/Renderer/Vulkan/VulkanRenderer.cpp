// VulkanRenderer.cpp
// Last update 27/5/2021 by Madman10K
#include <Renderer/Window/Window.hpp>
#include "VulkanRenderer.hpp"
// BAD BAD BAD!!!!!!!!!!!!
#include <stdexcept>


#include "Components/VKCamera.hpp"
#include "Components/VKFramebuffer.hpp"
#include "Components/VKMesh.hpp"
#include "Components/VKShader.hpp"



void UVK::VulkanRenderer::createInstance()
{
    // Setup versions, name, etc
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_2;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pApplicationName = "Untitled Vulkan Game Engine VK";
    appInfo.pEngineName = "Untitled Vulkan Game Engine";
    appInfo.pNext = nullptr;

    // Binds our application info to our application or something similar idk
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Array of extensions
    std::vector<const char*> instanceExtensions;

    // Extensions, number of extensions and array of extension names
    uint32_t extensionCount = 0;
    const char** extensions;

    // Get all of the extensions
	extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

	// Add extensions to the list of extensions
	for(size_t i = 0; i < extensionCount; i++)
	{
		instanceExtensions.push_back(extensions[i]);
	}

	// Check if instance extensions are supported
    if (!checkExtensionSupport(&instanceExtensions))
    {
        logger.consoleLog("Vulkan instance does not a support the required instance extensions", UVK_LOG_TYPE_ERROR);
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Instance", UVK_LOG_TYPE_ERROR);
    }
}

bool UVK::VulkanRenderer::checkExtensionSupport(std::vector<const char *> *extensions)
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // List of VkExtensionProperties with initial size = to count
    std::vector<VkExtensionProperties>extensionsList(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsList.data());

    // Extension checking
    for(const auto& extensionCheck : *extensions)
    {
        bool hasExtension = false;

        for (const auto& extension : extensionsList)
        {
            if (strcmp(extensionCheck, extension.extensionName) == 0)
            {
                hasExtension = true;
                break;
            }
        }

        if (!hasExtension)
        {
            return false;
        }
    }
    return true;
}

void UVK::VulkanRenderer::start()
{
    currentWindow.createWindow();
    createInstance();
    getPhysicalDevice();
    createLogicalDevice();
}

void UVK::VulkanRenderer::render()
{

}

void UVK::VulkanRenderer::cleanup()
{
    destroyLogicalDevice();
    destroyInstance();
}

void UVK::VulkanRenderer::run()
{
    start();

    GLfloat deltaTime;
    GLfloat lastTime = 0;

    while (!glfwWindowShouldClose(currentWindow.getWindow()))
    {
        glfwPollEvents();

        auto now = (float)glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        render();
    }

    cleanup();
}

void UVK::VulkanRenderer::destroyInstance()
{
    vkDestroyInstance(instance, nullptr);
}

void UVK::VulkanRenderer::getPhysicalDevice()
{
    uint32_t deviceCount = 0;

    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    // if doesn't support vulkan or no devices
    if (deviceCount == 0)
    {
        logger.consoleLog("Couldn't find any devices or any that support Vulkan", UVK_LOG_TYPE_ERROR);
    }

    std::vector<VkPhysicalDevice> deviceList(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, deviceList.data());

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

bool UVK::VulkanRenderer::checkDeviceSuitability(VkPhysicalDevice physicalDevice)
{
    // Check for properties
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

    // Check for features
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

    VKQueueFamilyLocation location = getQueueFamilies();

    return location.isValid();
}

UVK::VKQueueFamilyLocation UVK::VulkanRenderer::getQueueFamilies() const
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

        if (familyLocation.isValid())
        {
            break;
        }
    }
    return familyLocation;
}

void UVK::VulkanRenderer::createLogicalDevice()
{
    float priority = 1.0f;
    VKQueueFamilyLocation location = getQueueFamilies();

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = location.graphicsFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &priority; // highest priority

    VkPhysicalDeviceFeatures deviceFeatures = {};
    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.enabledExtensionCount = 0;
    deviceCreateInfo.ppEnabledExtensionNames = nullptr;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    VkResult result = vkCreateDevice(device.physicalDevice, &deviceCreateInfo, nullptr, &device.logicalDevice);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan logical device", UVK_LOG_TYPE_ERROR);
    }

    // get global class access to queue
    vkGetDeviceQueue(device.logicalDevice, location.graphicsFamily, 0, &queue);
}

void UVK::VulkanRenderer::destroyLogicalDevice() const
{
    vkDestroyDevice(device.logicalDevice, nullptr);
}
