// GLMesh.hpp
// Last update 3/17/2021 by Madman10K
#pragma once
#include "GLShader.hpp"
//#include <Core.hpp>


namespace UVK
{
    class GLMesh
    {
    public:
		GLMesh() = default;

		void createMesh(GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum);
		void render();
		void clear();

	private:
		GLuint VAO, VBO, IBO;
		GLsizei indexCount;
    };
}
