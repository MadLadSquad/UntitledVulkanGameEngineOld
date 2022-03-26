#include "Utility.hpp"
#include <UVKShaderCompiler/Src/Functions.hpp>

bool UVK::QueueFamilyIndices::valid() const noexcept
{
    return graphicsFamily >= 0 && presentationFamily >= 0;
}

std::vector<char> UVK::VKShader::getShaderBytecode() const noexcept
{
    auto hash = USC::getShaderHash(name.c_str());
    bool bFound = false;
    for (const auto& a : std_filesystem::directory_iterator("../Generated"))
    {
        if (!a.is_directory())
        {
            if (a.path() == std_filesystem::path("../Generated/" + hash + ".spv"))
            {
                bFound = true;
                break;
            }
        }
    }

    if (!bFound)
        USC::recompileShaders();

    std::ifstream in("../Generated/" + hash + ".spv", std::ios::ate | std::ios::binary);
    if (!in.is_open())
    {
        logger.consoleLog("Failed to load file!", UVK_LOG_TYPE_ERROR);
        std::terminate();
    }

    std::vector<char> returnVal(in.tellg());
    in.seekg(0);
    in.read(returnVal.data(), returnVal.size());
    in.close();

    return returnVal;
}

UVK::VKShader::VKShader(const char* fname) noexcept
{
    init(fname);
}

void UVK::VKShader::init(const char* fname) noexcept
{
    name = fname;
    if (name.ends_with(".vert"))
        type = VKShaderType::VK_SHADER_TYPE_VERTEX;
    else if (name.ends_with(".frag"))
        type = VKShaderType::VK_SHADER_TYPE_FRAGMENT;
    else if (name.ends_with(".geom"))
        type = VKShaderType::VK_SHADER_TYPE_GEOMETRY;
    else if (name.ends_with(".comp"))
        type = VKShaderType::VK_SHADER_TYPE_COMPUTE;
    else if (name.ends_with(".tesc"))
        type = VKShaderType::VK_SHADER_TYPE_TESSELLATION_CONTROL;
    else if (name.ends_with(".tese"))
        type = VKShaderType::VK_SHADER_TYPE_TESSELLATION_EVALUATION;
    else
        type = VKShaderType::VK_SHADER_TYPE_NONE;
}

void UVK::VKShader::each(const std::function<void(VKShader&)>& func) noexcept
{
    for (auto& a : std_filesystem::recursive_directory_iterator("../Content/"))
    {
        if (!a.is_directory())
        {
            VKShader shader(a.path().string().c_str());
            if (shader.type == VKShaderType::VK_SHADER_TYPE_NONE)
                continue;
            func(shader);
        }
    }
}
