// VKShader.hpp
// Last update 12/8/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

namespace UVK
{
    struct VKDevice;

    /**
     * @brief Vulkan specific spirv shader class
     */
    class VKShader
    {
    public:
        VKShader() = default;
        explicit VKShader(VKDevice* device);


        void createShader(const std::string& file);
        void useShader();
    private:
        friend class VKGraphicsPipeline;
        VKDevice* device;
        VkShaderModule shaderModule;

        void createShaderModule(const std::vector<char>& buffer);
        void destroyShaderModule();
    };
}
