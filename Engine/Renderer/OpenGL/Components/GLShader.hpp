// GLShader.hpp
// Last update 2/24/2021 by Madman10K
#pragma once
#include <GL/glew.h>

#include <Core.hpp>

namespace UVK
{
    class GLShader
    {
    public:
        GLShader() = delete;
        GLShader(const char* vLocation, const char* fLocation)
        {

        }


        GLuint& getProjectionLocation()
        {
            return uniformProjection;
        }

        [[maybe_unused]] GLuint& getModelLocation()
        {
            return uniformModel;
        }

        [[maybe_unused]] GLuint& getViewLocation()
        {
            return uniformView;
        }
    private:
        void clearShader();
        void createShader();
        void addShader(const char* vLoc, const char* fLoc);

        std::vector<unsigned char> vertexShader;
        std::vector<unsigned char> fragmentShader;

        GLuint shaderID = 0;
        GLuint uniformProjection = 0;
        GLuint uniformModel = 0;
        GLuint uniformView = 0;
    };
}


