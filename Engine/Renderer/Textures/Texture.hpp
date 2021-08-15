// Texture.hpp
// Last update 1/8/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    /**
     * @brief Texture for multiple targets including imgui, opengl and vulkan
     */
    class Texture
    {
    public:
        Texture() = default;
        explicit Texture(std::string loc)
            : location(std::move(loc)) {}
        void load();

        void destroy();


        [[maybe_unused]] std::string& getLocation() { return location; }
        int& getWidth() { return width; }
        int& getHeight() { return height; }
        GLuint& getImage() { return image; };
        void loadImgui();
        void useTexture() const;
    private:
        unsigned char* gen();

        friend class GLPipeline;
        friend class Editor;

        std::string location;
        int width = 0;
        int height = 0;
        GLuint image = 0;
    };
}

