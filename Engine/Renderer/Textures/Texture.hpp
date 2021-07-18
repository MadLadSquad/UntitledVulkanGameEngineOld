// Texture.hpp
// Last update 17/7/2021 by Madman10K
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

    private:
        unsigned char* gen();

        friend class GLPipeline;
        friend class Editor;
        void loadImgui();
        void useTexture() const;

        std::string location;
        int width = 0;
        int height = 0;
        GLuint image = 0;
    };
}

