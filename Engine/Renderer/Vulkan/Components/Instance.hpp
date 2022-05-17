#pragma once

namespace UVK
{
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* message, void* userData) noexcept
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
        ~VKInstance() = default;
        void create() noexcept;
        void destroy() noexcept;
        VkInstance& data() noexcept;
    private:
        static bool checkInstanceExtensionsSupport(const char** extensions, uint32_t count) noexcept;
        static bool checkValidationLayerSupport(const std::vector<const char*>& validationLayers) noexcept;

        VkInstance instance;
        VkDebugReportCallbackEXT callback;

        void createDebugCallback() noexcept;
    };
}