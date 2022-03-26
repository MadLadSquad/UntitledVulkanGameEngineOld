#pragma once
#include <Core/Types.hpp>
#include <Core/Defines.hpp>

namespace UVK
{
    /**
     * @brief Texture for multiple targets including imgui, opengl and vulkan
     */
    class UVK_PUBLIC_API Texture
    {
    public:
        Texture() = default;
        explicit Texture(std::string loc)
            : location(std::move(loc)) {}
        void load() noexcept;

        void destroy() noexcept;

        [[maybe_unused]] std::string& getLocation() noexcept { return location; }
        int& getWidth() noexcept { return width; }
        int& getHeight() noexcept { return height; }
        uint32_t& getImage() noexcept { return image; };
        void loadImgui() noexcept;
        void useTexture() const noexcept;
    private:
        unsigned char* gen() noexcept;

        friend class GLPipeline;
        friend class Editor;

        std::string location;
        int width = 0;
        int height = 0;
        uint32_t image = 0;
    };
}

