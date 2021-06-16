// GLRenderer.cpp
// Last update 15/6/2021 by Madman10K
#include <GL/glew.h>
#include "GLRenderer.hpp"
#include "../../Core/Events/Events.hpp"
#include <Core/Registry.hpp>
#include <Renderer/OpenGL/Pipeline/GLPipeline.hpp>

void UVK::GLRenderer::start(UVK::Level* level) const noexcept
{
    GLPipeline pipeline(bEditor, level);

    while (!glfwWindowShouldClose(currentWindow.getWindow()))
    {
        pipeline.tick();
    }

    pipeline.end();
}
// This is here for when you want to debug, just plop it after creating the pipeline
/*registry.createActor("Maikati");
pool.each([&](entt::entity ent){
    if (registry.getComponent<CoreComponent>(ent).name == "Maikati")
    {
        unsigned int indices[] = {
                0, 3, 1,
                1, 3, 2,
                2, 3, 0,
                0, 1, 2
        };

        GLfloat vertices[] = {
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.5f, 1.0f
        };

        registry.getComponent<CoreComponent>(ent).devName = "a";
        auto& a = registry.addComponent<MeshComponentRaw>(ent);
        a.createMesh(vertices, indices, 20, 12, "../Content/Engine/defaultvshader.gl", "../Content/Engine/defaultfshader.gl", SHADER_IMPORT_TYPE_FILE);
        a.rotation = FVector(0.0f, 0.0f, 0.0f);
        //auto& b = registry.addComponent<AudioComponent3D>(ent);
        //b.play("and.wav", true, 1.0f, 1.0f, FVector(15.0f, 0.0f, 0.0f));
    }
});
 */