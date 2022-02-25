// Instance.cpp
// Last update 21/12/2021 by Madman10K
#include "Instance.hpp"
#include <vulkan/vulkan.h>
#include <glfw3.h>

void UVK::VKInstance::create()
{
    // Metadata for the instance
    constexpr VkApplicationInfo applicationInfo =
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "UntitledVulkanGameEngine",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "UntitledVulkanGameEngine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_3
    };

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    if (!checkInstanceExtensionsSupport(glfwExtensions, glfwExtensionCount))
    {
        logger.consoleLog("Couldn't load all required extensions!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    // Creation information for the Vulkan instance
    const VkInstanceCreateInfo instanceInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames = glfwExtensions,
    };

    auto result = vkCreateInstance(&instanceInfo, nullptr, &instance);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Could not create an error! Error code: ", UVK_LOG_TYPE_ERROR, result);
        throw std::runtime_error(" ");
    }
}

void UVK::VKInstance::destroy()
{
    vkDestroyInstance(instance, nullptr);
}

bool UVK::VKInstance::checkInstanceExtensionsSupport(const char** extensions, uint32_t count)
{
    uint32_t extensionsNum = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsNum, nullptr);

    std::vector<VkExtensionProperties> extensionProperties(extensionsNum);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsNum, extensionProperties.data());

    for (size_t i = 0; i < count; i++)
    {
        bool bHasExtension = false;

        for (size_t j = 0; j < extensionsNum; j++)
        {
            if (strcmp(extensions[i], extensionProperties[j].extensionName) == 0)
            {
                bHasExtension = true;
                goto exit_nested_loop;
            }
        }
exit_nested_loop:
        if (!bHasExtension)
            return false;
    }
    return true;
}

VkInstance& UVK::VKInstance::data()
{
    return instance;
}
