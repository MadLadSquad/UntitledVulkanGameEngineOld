#pragma once
#include <array>
#include <vulkan/vulkan.h>
#include <vector>
#include <Core/Types.hpp>

namespace UVK
{
    class VKDevice;
    constexpr std::array<const char*, 2> deviceExtensions =
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_EXT_CUSTOM_BORDER_COLOR_EXTENSION_NAME,
    };

    struct SwapchainDetails
    {
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        std::vector<VkSurfaceFormatKHR> surfaceFormats;
        std::vector<VkPresentModeKHR> presentationModes;
    };

    enum class VKShaderType
    {
        VK_SHADER_TYPE_NONE = 0,
        VK_SHADER_TYPE_VERTEX = 0x00000001,
        VK_SHADER_TYPE_FRAGMENT = 0x00000010,
        VK_SHADER_TYPE_GEOMETRY = 0x00000008,
        VK_SHADER_TYPE_COMPUTE = 0x00000020,
        VK_SHADER_TYPE_TESSELLATION_CONTROL = 0x00000002,
        VK_SHADER_TYPE_TESSELLATION_EVALUATION = 0x00000004,
    };

    struct VKShader
    {
    public:
        VKShader() = default;
        explicit VKShader(const char* fname) noexcept;
        void init(const char* fname) noexcept;

        [[nodiscard]] std::vector<char> getShaderBytecode() const noexcept;
        static void each(const std::function<void(VKShader&)>& func) noexcept;

        std::string name;
        VKShaderType type = VKShaderType::VK_SHADER_TYPE_NONE;
    private:
        friend class GraphicsPipeline;

        VkPipelineShaderStageCreateInfo info{};
        VkShaderModule module{};
    };

    struct QueueFamilyIndices
    {
        int graphicsFamily = -1;
        int presentationFamily = -1;

        [[nodiscard]] bool valid() const noexcept;
    };

    struct SwapchainImage
    {
        VkImage image;
        VkImageView imageView;
        void createImage(const FVector2& size, const VkFormat& format, const VkImageTiling& tiling, const VkImageUsageFlags& usageFlags, const VkMemoryPropertyFlags& propertyFlags, VkDeviceMemory& memory, VKDevice& device, uint32_t mipLevels = 1, VkSampleCountFlagBits sampleCountFlagBits = VK_SAMPLE_COUNT_1_BIT);
        static VkFormat findBestImageFormat(const std::vector<VkFormat>& formats, const VkImageTiling& tiling, VkFormatFeatureFlags featureFlags, VKDevice& device);
    };

    struct VKVertex
    {
        FVector pos;
        FVector4 colour;
        FVector2 uv;
    };

    struct VP
    {
        glm::mat4 view;
        glm::mat4 projection;
    };

    struct Model
    {
        glm::mat4 model;
    };
}