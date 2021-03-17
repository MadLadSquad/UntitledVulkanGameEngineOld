// Components.hpp
// Last update 3/17/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <Audio/2D/Audio2D.hpp>

namespace UVK
{
    UVK_API struct CoreComponent
    {
        std::string name;
        uint64_t id;
    };

    UVK_API struct MeshComponentRaw
    {    
        void createMesh(GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, const char* vertexShader, const char* fragmentShader, ShaderImportType type)
        {
            mesh = new GLMesh();
            shader = new GLShader();

            mesh->createMesh(vertices, indices, vertexNum, indexNum);

            switch (type)
            {
            case SHADER_IMPORT_TYPE_FILE:
                shader->createFromFile(vertexShader, fragmentShader);
                break;
            case SHADER_IMPORT_TYPE_STRING:
                shader->createFromString(vertexShader, fragmentShader);
                break;
            case SHADER_IMPORT_TYPE_SPIR:
                logger.consoleLog("SPIR-V in OpenGL not implemented yet!", ERROR);
                break;
            }
        }
        
        void render(glm::mat4 projection, Model& mat)
        {   
            shader->useShader();
            uniformModel = shader->getModelLocation();
            uniformProjection = shader->getProjectionLocation();

            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(mat.getModel()));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

            mesh->render();
        }

        void clearMesh()
        {
            mesh->clear();
            shader->clearShader();
            
            delete mesh, shader;
        }
        
    private:
        glm::mat4* model;
        //FVector translation;
        //FVector scale;
        //FVector rotation;
        //float degrees;
        
        GLuint uniformModel;
        GLuint uniformProjection;

        GLMesh* mesh;
        GLShader* shader;
    };

    UVK_API struct PointLightComponent
    {

    };

    UVK_API struct SpotlightComponent
    {

    };

    UVK_API struct DirectionalLightComponent
    {

    };

    struct DirectionalAudioComponent
    {

    };

#ifndef __MINGW32__
    struct AudioComponent2D
    {
    public:
        void play()
        {
            thread = std::thread([&]()
            {
                audio2d.init();
                logger.consoleLog("Initialised audio system", SUCCESS);

                buffer = audio2d.addSoundEffect(loc.c_str());
                logger.consoleLog("Added sound effect", SUCCESS);

                UVK::SoundSource2D src(bRepeat, pitch, gain);

                logger.consoleLog("Playing audio", SUCCESS);
                src.play(buffer);

            });
        }

        void stopAudio()
        {
            thread.join();
        }

        //ALuint& getBuffer()
        //{
        //    return buffer;
        //}

        std::string loc;
        bool bRepeat = false;
        float pitch = 1.0f;
        float gain = 1.0f;
    private:

        ALuint buffer;
        std::thread thread;
    };

#else
    struct AudioComponent2D
    {
        char foo;
        std::string loc;
        bool bRepeat = false;
        float pitch = 1.0f;
        float gain = 1.0f;
    };
#endif

}