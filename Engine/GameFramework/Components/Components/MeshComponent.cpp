#include "MeshComponent.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Renderer/Textures/Texture.hpp>

void UVK::MeshComponent::create(UVK::String location, VKDevice &dev, Commands& cmd, VKDescriptors& desc) noexcept
{
    device = &dev;
    commands = &cmd;
    descriptors = &desc;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(location, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    if (scene == nullptr)
    {
        logger.consoleLog("Couldn't load model at location: ", UVK_LOG_TYPE_ERROR, location);
        std::terminate();
    }
    std::vector<std::string> textureNames(scene->mNumMaterials);
    for (size_t i = 0; i < scene->mNumMaterials; i++)
    {
        aiMaterial* material = scene->mMaterials[i];
        textureNames[i] = "";
        if (material->GetTextureCount(aiTextureType_DIFFUSE))
        {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {
                textureNames[i] = path.data;
            }
        }
    }
    textures.emplace_back
    (
        Texture("../Content/Engine/missing.png", *device, *commands, *descriptors,
        {
                .magFilter = TEXTURE_FILTERING_MODE_NEAREST,
                .minFilter = TEXTURE_FILTERING_MODE_NEAREST,
        })
    );
    textures.front().load();
    matids.resize(textureNames.size());
    for (size_t i = 0; i < textureNames.size(); i++)
    {
        if (textureNames[i].empty() || !std_filesystem::exists(std_filesystem::path(textureNames[i])))
            matids[i] = 0;
        else
        {
            textures.emplace_back(textureNames[i], *device, *commands, *descriptors);
            textures.back().load();
            matids[i] = textures.size() - 1;
        }
    }

    //mat.resize(textureNames.size());

    //for (size_t i = 0; i < textureNames.size(); i++)
    //{
    //    if (textureNames[i].empty())
    //    {
    //        mat[i] = 0;
    //    }
    //    else
    //    {
    //        textures.emplace_back(Texture(textureNames[i], *device, *commands, *descriptors));
    //        textures.back().load();
    //        mat[i] = textures.size() - 1;
    //    }
    //}

    loadNode(scene->mRootNode, scene);
}

void UVK::MeshComponent::update(size_t index, uint32_t currentImage, GraphicsPipeline& pipeline) noexcept
{
    model = glm::mat4(1.0);
    Math::translate(model, translation);
    Math::rotate(model, rotation);
    Math::scale(model, scale);

    auto& cmd = commands->getCommandBuffers()[currentImage];
    vkCmdPushConstants(cmd, pipeline.getPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(Model), &model);
    for (size_t i = 0; i < meshes.size(); i++)
    {
        VkBuffer vertexBuffers[] = { meshes[i].getVertexBuffer().getBuffer() };
        VkDescriptorSet descriptorSets[] = { descriptors->getDescriptorSets()[currentImage], descriptors->getSamplerDescriptorSets()[textures[matids[i]].getImage()] };
        VkDeviceSize offsets[] = { 0 };

        vkCmdBindVertexBuffers(cmd, 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(cmd, meshes[i].getIndexBuffer().getBuffer(), 0, VK_INDEX_TYPE_UINT32);

        //uint32_t dynamicOffset = static_cast<uint32_t>(modelUniformAlignment) * index;

        vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getPipelineLayout(), 0, 2, descriptorSets, 0, nullptr);

        vkCmdDrawIndexed(cmd, meshes[i].indexCount(), 1, 0, 0, 0);
    }
}

void UVK::MeshComponent::destroy() noexcept
{
    for (auto& a : meshes)
        a.destroyVertexBuffer();
    for (auto& a : textures)
        a.destroy();
}

void UVK::MeshComponent::loadNode(aiNode* node, const aiScene* scene) noexcept
{
    for (size_t i = 0; i < node->mNumMeshes; i++)
        loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    for (size_t i = 0; i < node->mNumChildren; i++)
        loadNode(node->mChildren[i], scene);
}

void UVK::MeshComponent::loadMesh(aiMesh* mesh, const aiScene* scene) noexcept
{
    std::vector<VKVertex> vertices;
    std::vector<uint32_t> indices;

    vertices.resize(mesh->mNumVertices);
    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        vertices[i].pos = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        if (mesh->mTextureCoords[0])
            vertices[i].uv = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
        else
            vertices[i].uv = { 0.0f, 0.0f };
        vertices[i].colour = { 1.0f, 1.0f, 1.0f, 1.0f };
    }
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    VKMesh m;
    meshes.push_back(m);
    meshes.back() = VKMesh(*device, device->getGraphicsQueue(), commands->getCommandPool(), std::move(vertices), std::move(indices));
}
