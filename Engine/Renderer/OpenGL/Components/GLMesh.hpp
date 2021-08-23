// GLMesh.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include "GLShader.hpp"
//#include <Core.hpp>


namespace UVK
{
    /**
     * @brief OpenGL specific mesh class
     */
    class GLMesh
    {
    public:
		GLMesh() = default;

		void createMesh(float* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum);
		void render() const;
		void clear();

	private:
		uint32_t VAO, VBO, IBO;
		int indexCount;
    };
}
