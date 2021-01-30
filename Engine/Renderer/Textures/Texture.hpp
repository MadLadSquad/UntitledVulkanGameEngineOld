#pragma once
#include <Core.hpp>
#include <stb_image.h>

class Texture
{
public:
    Texture() = delete;
    explicit Texture(std::string loc)
    {
        location = std::move(loc);
        width = 0;
        height = 0;
        image = 0;
    }


    void load();
    void destroy();


    std::string& getLocation() { return location; }
    int& getWidth() { return width; }
    int& getHeight() { return height; }
    GLuint& getImage() { return image; };

private:
    std::string location;
    int width;
    int height;
    GLuint image;
};
