// Components.hpp
// Last update 4/20/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include <glm/gtx/quaternion.hpp>
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <../Renderer/OpenGL/Components/GLCamera.hpp>
#include <Audio/Audio2D.hpp>
#include <Audio/Audio3D.hpp>


namespace UVK
{
    /**
     * @brief A mesh component flag states they given object's light rendering properties (Not yet implemented)
     * @param MESH_FLAG_STATIC - A static object that never moves, always receives baked lighting
     * @param MESH_FLAG_STATIONARY - A stationary object is rendered with baked lighting and moves to dynamic lighting after movement
     * @param MESH_FLAG_DYNAMIC - A dynamic object that always moves which makes it always render with dynamic lighting
     */
    enum MeshComponentFlags
    {
        MESH_FLAG_STATIC,
        MESH_FLAG_STATIONARY,
        MESH_FLAG_DYNAMIC
    };

    /**
     * @brief The base component every entity has
     * @param name - the name of the entity
     * @param id - the universal unique identifier(UUID) of an entity (Not yet implemented)
     */
    UVK_API struct CoreComponent
    {
        std::string name;
        uint64_t id;
    };

    /**
     * @brief A mesh component used for debugging. It takes an array of vertices and indices instead of a mesh filename
     */
    struct MeshComponentRaw
    {    
        void createMesh(GLfloat* vertices, uint32_t* indices, uint32_t vertexNum, uint32_t indexNum, const char* vertexShader, const char* fragmentShader, ShaderImportType type)
        {
            fShader = fragmentShader;
            vShader = vertexShader;
            impType = type;
            for (int i = 0; i < indexNum; i++)
            {
                index.push_back(indices[i]);
            }

            for (int i = 0; i < vertexNum; i++)
            {
                vertex.push_back(vertices[i]);
            }

            mesh.createMesh(vertices, indices, vertexNum, indexNum);

            switch (type)
            {
            case SHADER_IMPORT_TYPE_FILE:
                shader.createFromFile(vertexShader, fragmentShader);
                break;
            case SHADER_IMPORT_TYPE_STRING:
                shader.createFromString(vertexShader, fragmentShader);
                break;
            case SHADER_IMPORT_TYPE_SPIR:
                logger.consoleLog("SPIR-V in OpenGL not implemented yet!", UVK_LOG_TYPE_ERROR);
                break;
            }

            translation = FVector(1.0f, 1.0f, 1.0f);
            rotation = FVector4(1.0f, 1.0f, 1.0f, 0.0f);
            scale = FVector(1.0f, 1.0f, 1.0f);
        }
        
        void render(glm::mat4 projection, GLCamera& camera)
        {
            mat = glm::mat4(1.0f);
            shader.useShader();

            uniformModel = shader.getModelLocation();
            uniformProjection = shader.getProjectionLocation();
            uniformView = shader.getViewLocation();

            glm::mat4 rot = glm::toMat4(glm::quat(rotation));

            mat = glm::translate(mat, translation);
            mat = mat * rot;
            mat = glm::scale(mat, scale);

            glUniformMatrix4fv((int)uniformModel, 1, GL_FALSE, glm::value_ptr(mat));
            glUniformMatrix4fv((int)uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv((int)uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

            mesh.render();
        }

        void clearMesh()
        {
            mesh.clear();
            shader.clearShader();

            index.clear();
            vertex.clear();
        }

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

//#ifndef __MINGW32__
    /**
     * @brief An audio source without distance attenuation
     */
    /*
   struct AudioComponent2D
   {
   public:
       void play(const char* location, bool bRepeat, float pitchArg, float gainArg)
       {
           loc = location;
           bAudioRepeat = bRepeat;
           pitch = pitchArg;
           gain = gainArg;

           thread = std::thread([&]()
           {
               logger.consoleLog("Initialised audio system", UVK_LOG_TYPE_SUCCESS);

               buffer = audio.addSoundEffect(loc.c_str());
               logger.consoleLog("Added sound effect", UVK_LOG_TYPE_SUCCESS);

               UVK::SoundSource2D src(bRepeat, pitch, gain);

               logger.consoleLog("Playing audio", UVK_LOG_TYPE_SUCCESS);
               src.play(buffer);
           });
       }

       void stopAudio()
       {
           thread.detach();
           thread.~thread();
       }

       std::string loc;
       bool bAudioRepeat;
       float pitch;
       float gain;

       ALuint buffer;
       std::thread thread;
   private:

   };

#else
   struct AudioComponent2D
   {
       char foo;
       std::string loc;
       bool bAudioRepeat = false;
       float pitch = 1.0f;
       float gain = 1.0f;

       void stopAudio()
       {
       }

       void play(const char* location, bool bRepeat, float pitchArg, float gainArg)
       {
       }
   };
#endif

#ifndef __MINGW32__
    /**
     * @brief An audio component with a location and distance audio attenuation
     *//*
    struct AudioComponent3D
    {
    public:
        void play(const char* location, bool bRepeat, float pitchArg, float gainArg, FVector translation)
        {
            loc = location;
            bAudioRepeat = bRepeat;
            pitch = pitchArg;
            gain = gainArg;
            trs = translation;

            thread = std::thread([&]()
            {
                logger.consoleLog("Initialised audio system", UVK_LOG_TYPE_SUCCESS);

                buffer = audio.addSoundEffect(loc.c_str());

                logger.consoleLog("Added sound effect", UVK_LOG_TYPE_SUCCESS);

                UVK::SoundSource3D src(bRepeat, pitch, gain, trs);

                logger.consoleLog("Playing audio", UVK_LOG_TYPE_SUCCESS);
                src.play(buffer);
            });
        }

        void stopAudio()
        {
            thread.detach();
            thread.~thread();
        }

        std::string loc;
        bool bAudioRepeat;
        float pitch;
        float gain;
        FVector trs;

        ALuint buffer;
        std::thread thread;
    private:

    };
#else
    struct AudioComponent3D
    {
        void stopAudio()
        {

        }

        void play(const char* location, bool bRepeat, float pitchArg, float gainArg, FVector translation)
        {

        }
        FVector trs;
        std::string loc;
        bool bAudioRepeat = false;
        float pitch = 1.0f;
        float gain = 1.0f;
    };
#endif
    */
}