// Texture.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <stb/stb_image.h>

namespace UVK
{
    /**
     * @brief Texture for multiple targets including imgui, opengl and vulkan
     */
    class Texture
    {
    public:
        Texture() = default;
        explicit Texture(const std::string& loc)
                :location(loc)
        {

        }


        void load();
        void loadImgui();
        void destroy();
        void useTexture() const;

        [[maybe_unused]] std::string& getLocation() { return location; }
        int& getWidth() { return width; }
        int& getHeight() { return height; }
        GLuint& getImage() { return image; };

    private:
        std::string location;
        int width = 0;
        int height = 0;
        GLuint image = 0;
    };
}

