// Texture.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <stb/stb_image.h>

namespace UVK
{
    class Texture
    {
    public:
        Texture() = delete;
        explicit Texture(const std::string& loc)
                :location(loc)
        {

        }


        void load();
        void destroy();


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

