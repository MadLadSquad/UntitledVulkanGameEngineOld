// VKInstance.cpp
// Last update 2/7/2021 by Madman10K
#include "VKInstance.hpp"
#ifndef __APPLE__
void UVK::VKInstance::create()
{
    // Setup versions, name, etc
    VkApplicationInfo appInfo =
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .pApplicationName = "Untitled Vulkan Game Engine VK",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "Untitled Vulkan Game Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_2
    };

    // Binds our application info to our application or something similar idk
    VkInstanceCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo
    };

    // Array of extensions
    std::vector<UVK::String> instanceExtensions;

    // Extensions, number of extensions and array of extension names
    uint32_t extensionCount = 0;
    UVK::String* extensions;

    // Get all of the extensions
    extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

    // Add extensions to the list of extensions
    for(size_t i = 0; i < extensionCount; i++)
    {
        instanceExtensions.push_back(extensions[i]);
    }

    // This extension doesn't work on latest NVidia and AMD, and doesn't work at all on Linux, Mac, iOS and Android
    //instanceExtensions.push_back(VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME);

    // Check if instance extensions are supported
    if (!checkExtensionSupport(&instanceExtensions))
    {
        logger.consoleLog("Vulkan instance does not a support the required instance extensions", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Instance", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

void UVK::VKInstance::destroy()
{
    vkDestroyInstance(instance, nullptr);
}

bool UVK::VKInstance::checkExtensionSupport(std::vector<UVK::String>* extensions)
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // List of VkExtensionProperties with initial size = to count
    std::vector<VkExtensionProperties>extensionsList(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsList.data());

    // Extension checking, that time complexity doe
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
#endif
