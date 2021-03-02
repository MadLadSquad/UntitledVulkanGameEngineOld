// Texture.cpp
// Last update 2/7/2021 by Madman10K
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"



void UVK::Texture::load()
{
    unsigned char* img = stbi_load(location.c_str(), &width, &height, nullptr, 4);

    if (img == nullptr)
        return;

    glGenTextures(1, &image);
    glBindTexture(GL_TEXTURE_2D, image);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
}

void UVK::Texture::destroy()
{
    stbi_image_free(&image);
}
