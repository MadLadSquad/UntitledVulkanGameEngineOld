// MeshComponentRaw.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <GL/glew.h>
#include <glm/gtx/quaternion.hpp>
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <Renderer/Camera/Camera.hpp>

namespace UVK
{
    struct CoreComponent;
    class Actor;

    /**
     * @brief A mesh component used for debugging
     */
    struct UVK_PUBLIC_API MeshComponentRaw
    {
        void createMesh(UVK::Actor* currentActor, GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, UVK::String vertexShader, UVK::String fragmentShader, ShaderImportType type);
        void render(Camera& camera);
        void clearMesh();

        glm::mat4 mat;

        std::vector<uint32_t> index;
        std::vector<float> vertex;
        UVK::String fShader;
        UVK::String vShader;

        ShaderImportType impType;
    private:
        UVK::CoreComponent* core = nullptr;
        Actor* actor = nullptr;

        GLuint uniformModel = 0;
        GLuint uniformProjection = 0;
        GLuint uniformView = 0;

        GLMesh mesh;
        GLShader shader;
    };
}