// VKInstance.cpp
// Last update 28/5/2021 by Madman10K
#include "VKInstance.hpp"

void UVK::VKInstance::create()
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

void UVK::VKInstance::destroy()
{
    vkDestroyInstance(instance, nullptr);
}

bool UVK::VKInstance::checkExtensionSupport(std::vector<const char*>* extensions)
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
