// MeshComponentRaw.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <glm/gtx/quaternion.hpp>
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <../Renderer/OpenGL/Components/GLCamera.hpp>

namespace UVK
{
    /**
     * @brief A mesh component used for debugging
     */
    struct MeshComponentRaw
    {
        void createMesh(GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, const char* vertexShader, const char* fragmentShader, ShaderImportType type);
        void render(glm::mat4 projection, GLCamera& camera);
        void clearMesh();

        glm::mat4 mat;

        FVector rotation;
        FVector translation;
        FVector scale;

        std::vector<uint32_t> index;
        std::vector<float> vertex;
        std::string fShader;
        std::string vShader;

        ShaderImportType impType;
    private:
        GLuint uniformModel = 0;
        GLuint uniformProjection = 0;
        GLuint uniformView = 0;

        GLMesh mesh;
        GLShader shader;
    };
}