// VKUtility.hpp
// Last update 26/02/2022 by Madman10K
#pragma once
#include <array>

namespace UVK
{
    constexpr std::array<const char*, 1> deviceExtensions =
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
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
        explicit VKShader(const char* fname);
        void init(const char* fname);

        std::vector<char> getShaderBytecode() const;
        static void each(const std::function<void(VKShader&)>& func);

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

        bool valid() const;
    };

    struct SwapchainImage
    {
        VkImage image;
        VkImageView imageView;
    };
}