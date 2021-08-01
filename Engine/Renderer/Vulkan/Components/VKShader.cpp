// VKShader.cpp
// Last update 1/8/2021 by Madman10K
#include "VKShader.hpp"
#include "VKStructs.hpp"

void UVK::VKShader::useShader()
{

}

void UVK::VKShader::createShader(const std::string& file)
{
    std::ifstream in(file, std::ios::binary | std::ios::ate);
    std::vector<char> buffer;


    bool err = !in.is_open();
    if (!err)
    {
        size_t filesize = (size_t)in.tellg();
        buffer = std::vector<char>(filesize);
        in.seekg(0);
        in.read(buffer.data(), filesize);
        in.close();

        createShaderModule(buffer);
    }
    else
    {
        logger.consoleLog("Couldn't create shader with name: ", UVK_LOG_TYPE_ERROR, file);
    }
}

void UVK::VKShader::createShaderModule(const std::vector<char>& buffer)
{
    VkShaderModuleCreateInfo moduleCreateInfo = {};
    moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    moduleCreateInfo.codeSize = buffer.size();
    moduleCreateInfo.pCode = (uint32_t*)buffer.data();

    auto result = vkCreateShaderModule(device->logicalDevice, &moduleCreateInfo, nullptr, &shaderModule);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Error when creating a shader module!", UVK_LOG_TYPE_ERROR);
    }
}

UVK::VKShader::VKShader(UVK::VKDevice* dev)
{
    device = dev;
}

void UVK::VKShader::destroyShaderModule()
{
    vkDestroyShaderModule(device->logicalDevice, shaderModule, nullptr);
}
