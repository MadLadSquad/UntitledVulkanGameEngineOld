// Components.hpp
// Last update 3/17/2021 by Madman10K
#pragma once
#include <GL/glew.h>

#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <../Renderer/OpenGL/Components/GLCamera.hpp>
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
        
        void render(glm::mat4 projection, Model& mat, GLCamera& camera)
        {   
            shader->useShader();
            uniformModel = shader->getModelLocation();
            uniformProjection = shader->getProjectionLocation();
            uniformView = shader->getViewLocation();

            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(mat.getModel()));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
            mesh->render();
        }

        void clearMesh()
        {
            mesh->clear();
            shader->clearShader();
            
            delete mesh, shader;
        }
        
    private:
        glm::mat4* model = nullptr;
        
        GLuint uniformModel = 0;
        GLuint uniformProjection = 0;
        GLuint uniformView = 0;

        GLMesh* mesh = nullptr;
        GLShader* shader = nullptr;
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
        void play(const char* location, bool bRepeat, float pitch, float gain)
        {
            loc = location;
            this->bAudioRepeat = bRepeat;
            this->pitch = pitch;
            this->gain = gain;

            //thread = std::thread([&]()
           //{
            logger.consoleLog("Initialised audio system", SUCCESS);

            buffer = audio.addSoundEffect(loc);
            logger.consoleLog("Added sound effect", SUCCESS);

            UVK::SoundSource2D src(bRepeat, pitch, gain);

            logger.consoleLog("Playing audio", SUCCESS);
            src.play(buffer);
            //;});
            src.~SoundSource2D();
        }

        void stopAudio()
        {
            //thread.join();
        }

        const char* getLocation()
        {
            return loc;
        }

        bool getRepeat()
        {
            return bAudioRepeat;
        }

        float getPitch()
        {
            return pitch;
        }

        float getGain()
        {
            return gain;
        }
    private:
        const char* loc;
        bool bAudioRepeat;
        float pitch;
        float gain;

        ALuint buffer;
        //std::thread thread;
    };

#else
    struct AudioComponent2D
    {
        char foo;
        const char* loc;
        bool bAudioRepeat = false;
        float pitch = 1.0f;
        float gain = 1.0f;

        void stopAudio()
        {
            //thread.join();
        }

        const char* getLocation()
        {
            return loc;
        }

        bool getRepeat()
        {
            return bAudioRepeat;
        }

        float getPitch()
        {
            return pitch;
        }

        float getGain()
        {
            return gain;
        }
    };
#endif

#ifndef __MINGW32__
    struct AudioComponent3D
    {
    public:
        void play(const char* location, bool bRepeat, float pitch, float gain, FVector translation)
        {
            loc = location;
            bAudioRepeat = bRepeat;
            this->pitch = pitch;
            this->gain = gain;
            trs = translation;

            thread = std::thread([&]()
            {
                logger.consoleLog("Initialised audio system", SUCCESS);

                buffer = audio.addSoundEffect(loc);
                logger.consoleLog("Added sound effect", SUCCESS);
                
                //UVK::SoundSource3D src(bRepeat, pitch, gain, translation);
                
                logger.consoleLog("Playing audio", SUCCESS);
                //src.play(buffer);
            });
        }

        void stopAudio()
        {
            thread.join();
        }

        const char* getLocation()
        {
            return loc;
        }

        bool getRepeat()
        {
            return bAudioRepeat;
        }

        float getPitch()
        {
            return pitch;
        }

        float getGain()
        {
            return gain;
        }

        FVector getTranslation()
        {
            return trs;
        }
    private:
        const char* loc;
        bool bAudioRepeat;
        float pitch;
        float gain;
        FVector trs;

        ALuint buffer;
        std::thread thread;
    };
#else
    struct AudioComponent3D
    {
        std::string loc;
        bool bRepeat = false;
        float pitch = 1.0f;
        float gain = 1.0f;
    };
#endif
}