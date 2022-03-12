// Instance.cpp
// Last update 26/02/2022 by Madman10K
#include "Instance.hpp"
#ifdef DEVELOPMENT
    #define VK_DEBUG
#endif
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
        .apiVersion = VK_API_VERSION_1_2
    };

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> instanceExtensions;
    std::vector<const char*> instanceLayers;
    for (size_t i = 0; i < glfwExtensionCount; i++)
        instanceExtensions.push_back(glfwExtensions[i]);
#ifdef DEVELOPMENT
    instanceExtensions.push_back("VK_EXT_debug_report");
    instanceLayers.push_back("VK_LAYER_KHRONOS_validation");
#endif

    if (!checkInstanceExtensionsSupport(instanceExtensions.data(), instanceExtensions.size()))
    {
        logger.consoleLog("Couldn't load all required extensions!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    // Creation information for the Vulkan instance
    const VkInstanceCreateInfo instanceInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = static_cast<uint32_t>(instanceLayers.size()),
        .ppEnabledLayerNames = instanceLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size()),
        .ppEnabledExtensionNames = instanceExtensions.data(),
    };

    if (!checkValidationLayerSupport(instanceLayers))
    {
        logger.consoleLog("Couldn't create validation layers!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    auto result = vkCreateInstance(&instanceInfo, nullptr, &instance);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Could not create a Vulkan instance! Error code: ", UVK_LOG_TYPE_ERROR, result);
        throw std::runtime_error(" ");
    }
    createDebugCallback();
}

void UVK::VKInstance::destroy()
{
#ifdef DEVELOPMENT
    PFN_vkDestroyDebugReportCallbackEXT destroyDebugReportCallback = VK_NULL_HANDLE;
    destroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
    destroyDebugReportCallback(instance, callback, nullptr);
#endif
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

UVK::VKInstance::~VKInstance()
{
    destroy();
}

bool UVK::VKInstance::checkValidationLayerSupport(std::vector<const char*>& validationLayers)
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    for (auto& layerName : validationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

void UVK::VKInstance::createDebugCallback()
{
#ifdef DEVELOPMENT
    VkDebugReportCallbackCreateInfoEXT callbackCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
        .flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT,
        .pfnCallback = debugCallback
    };
    PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback = VK_NULL_HANDLE;
    CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    auto result = CreateDebugReportCallback(instance, &callbackCreateInfo, nullptr, &callback);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a debug callback! Error code: ", UVK_LOG_TYPE_ERROR, result);
        throw std::runtime_error(" ");
    }
#endif
}
