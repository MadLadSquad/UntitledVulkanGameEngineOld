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

        GLuint& getModelLocation()
        {
            return uniformModel;
        }

        GLuint& getViewLocation()
        {
            return uniformView;
        }
    private:
        void clearShader();
        void createShader();
        void addShader(const char* vLoc, const char* fLoc);

        std::vector<unsigned char> vertexShader;
        std::vector<unsigned char> fragmentShader;

        GLuint shaderID, uniformProjection, uniformModel, uniformView;
    };
}


