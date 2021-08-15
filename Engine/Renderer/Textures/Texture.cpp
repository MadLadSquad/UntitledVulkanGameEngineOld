// Texture.cpp
// Last update 17/7/2021 by Madman10K
#define STB_IMAGE_IMPLEMENTATION
#include "GL/glew.h"
#include "Texture.hpp"
#include <stb/stb_image.h>

void UVK::Texture::load()
{
    unsigned char* img = gen();

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif

    if (img != nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(img);
    }
}

void UVK::Texture::loadImgui()
{
    auto* img = gen();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif

    if (img != nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
        stbi_image_free(img);
    }
}

void UVK::Texture::destroy()
{
    glDeleteTextures(1, &image);
    
    image = 0;
    width = 0;
    height = 0;
}

void UVK::Texture::useTexture() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image);
}

unsigned char* UVK::Texture::gen() 
{
    unsigned char* img = stbi_load(static_cast<std::string>("../Content/" + location).c_str() , &width, &height, nullptr, 4);

    if (img == nullptr)
        return nullptr;

    glGenTextures(1, &image);
    glBindTexture(GL_TEXTURE_2D, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return img;
}
