#pragma once

#include "../../Core/API/Defines.h"
#ifdef Legacy


#include "../../ThirdParty/GLEW/include/GL/glew.h"
#include <vector>

namespace UVK
{ 
	class UVK_API GLMesh
	{
	public:
		GLMesh();
		~GLMesh();
		
		void CreateMesh(GLfloat* Vertices, uint32_t* Indices, uint32_t VertexNum, uint32_t IndexNum);
		void RenderMesh();
		void ClearMesh();
	private:
		GLuint VAO, VBO, IBO;
		GLsizei IndexCount;
	};
}
#endif