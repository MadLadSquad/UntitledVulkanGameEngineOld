// GLMesh.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include "GLShader.hpp"

namespace UVK
{
    /**
     * @brief OpenGL specific mesh class
     */
    class UVK_PUBLIC_API GLMesh
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
