#pragma once
#include <GL/glew.h>
#include <Core.hpp>


namespace UVK
{
    class GLMesh
    {
    public:
        GLMesh() = delete;
        GLMesh(GLfloat* vertices, uint32_t* indices, uint32_t numOfVertices, uint32_t numOfIndices);

        void render() const;

        void deleteMesh();
    private:
        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint IBO = 0;
        GLsizei indexCount = 0;
    };
}
