// GLMesh.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include <Core.hpp>


namespace UVK
{
    class GLMesh
    {
    public:
        GLMesh() = delete;
        GLMesh(GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum);

        void render() const;

        void deleteMesh();
    private:

        void createMesh(GLfloat* vertices, uint32_t* indices, uint32_t numOfVertices, uint32_t numOfIndices);

        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint IBO = 0;
        GLsizei indexCount = 0;
    };
}
