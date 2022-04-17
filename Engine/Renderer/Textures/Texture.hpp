#pragma once
#include <Core/Types.hpp>
#include <Core/Defines.hpp>
#include <vulkan/vulkan.h>
#include <Renderer/Vulkan/Components/Utility.hpp>

namespace UVK
{
    class VKDevice;
    class Commands;
    class VKDescriptors;

    enum [[maybe_unused]] TextureFilteringMode
    {
        TEXTURE_FILTERING_MODE_NEAREST = 0,
        TEXTURE_FILTERING_MODE_LINEAR = 1,
    };

    enum [[maybe_unused]] TextureWrapMode
    {
        TEXTURE_WRAP_MODE_REPEAT = 0,
        TEXTURE_WRAP_MODE_MIRRORED_REPEAT = 1,
        TEXTURE_WRAP_MODE_CLAMP_TO_EDGE = 2,
        TEXTURE_WRAP_MODE_CLAMP_TO_BORDER = 3,
        TEXTURE_WRAP_MODE_MIRROR_CLAMP_TO_EDGE = 4
    };

    enum [[maybe_unused]] TextureMipMapMode
    {
        TEXTURE_MIP_MAP_MODE_LINEAR = 1,
        TEXTURE_MIP_MAP_MODE_NEAREST = 0,
    };

    struct UVK_PUBLIC_API TextureSettings
    {
        TextureFilteringMode magFilter = TEXTURE_FILTERING_MODE_LINEAR;
        TextureFilteringMode minFilter = TEXTURE_FILTERING_MODE_LINEAR;
        // U = 0, V = 1, W = 2
        TextureWrapMode wrapModes[3] =
        {
            TEXTURE_WRAP_MODE_REPEAT,
            TEXTURE_WRAP_MODE_REPEAT,
            TEXTURE_WRAP_MODE_REPEAT,
        };
        FVector4 borderColour{ 0.0f, 0.0f, 0.0f, 1.0f };
        TextureMipMapMode mipMapMode = TEXTURE_MIP_MAP_MODE_LINEAR;
    };

    /**
     * @brief Texture for multiple targets including imgui, opengl and vulkan
     */
    class UVK_PUBLIC_API Texture
    {
    public:
        Texture() = default;
        // TODO: Remove
        explicit Texture(const std::string& loc);
        Texture(const std::string& loc, VKDevice& dev, Commands& cmd, VKDescriptors& desc, const TextureSettings& sett = {}) noexcept;
        void load() noexcept;

        void destroy() noexcept;


        [[maybe_unused]] std::string& getLocation() noexcept { return location; }
        int& getWidth() noexcept { return width; }
        int& getHeight() noexcept { return height; }
        size_t& getImage() noexcept { return descriptorLocation; };
        void loadImgui() noexcept;
        void useTexture() const noexcept;
    private:
        VKDevice* device = nullptr;
        Commands* commands = nullptr;
        VKDescriptors* descriptors = nullptr;

        unsigned char* gen() noexcept;
        void generateMipMaps();

        friend class GLPipeline;
        friend class Editor;

        std::string location;
        int width = 0;
        int height = 0;
        int channels = 0;

        size_t descriptorLocation = 0;
        uint32_t mipLevels = 1;
        // TODO: remove
        uint32_t tmp = 1;

        size_t size = 0;

        SwapchainImage image{};
        VkSampler textureSampler{};
        TextureSettings settings{};
    };
}

