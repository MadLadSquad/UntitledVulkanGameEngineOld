#pragma once
#include <Core.hpp>

namespace UVK
{
    class GLShader
    {
    public:
        GLShader() = delete;
        //GLShader()
        //{

        //}


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
        void addShader();

        GLuint shaderID, uniformProjection, uniformModel, uniformView;
    };
}


