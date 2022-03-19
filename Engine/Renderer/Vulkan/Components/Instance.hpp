// Instance.hpp
// Last update 26/02/2022 by Madman10K
#pragma once

namespace UVK
{
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* message, void* userData)
    {
        if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
        {
            logger.consoleLog("Vulkan Validation error: ", UVK_LOG_TYPE_ERROR, message);
            return VK_TRUE;
        }

        if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
        {
            logger.consoleLog("Vulkan Validation warning: ", UVK_LOG_TYPE_WARNING, message);
            return VK_FALSE;
        }

        return VK_FALSE;
    }

    class VKInstance
    {
    public:
        VKInstance() = default;
        ~VKInstance();
        void create();
        void destroy();
        VkInstance& data();
    private:
        static bool checkInstanceExtensionsSupport(const char** extensions, uint32_t count);
        static bool checkValidationLayerSupport(const std::vector<const char*>& validationLayers);

        VkInstance instance;
        VkDebugReportCallbackEXT callback;

        void createDebugCallback();

    };
}