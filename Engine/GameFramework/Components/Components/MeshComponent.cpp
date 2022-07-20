#include "MeshComponent.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Renderer/Textures/Texture.hpp>
#include <Core/Global.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>
#include <yaml-cpp/yaml.h>
#include <Renderer/Vulkan/VulkanRenderer.hpp>

namespace YAML
{
    template<>
    struct convert<UVK::FVector>
    {
        static Node encode(const UVK::FVector& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UVK::FVector& rhs) noexcept
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<UVK::FVector4>
    {
        static Node encode(const UVK::FVector4& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UVK::FVector4& rhs) noexcept
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
}

// Operator overloads for future transform component
extern YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector& vect) noexcept;
extern YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector4& vect) noexcept;

void UVK::MeshComponent::create(UVK::String location, VKDevice &dev, Commands& cmd, VKDescriptors& desc, UVK::CoreComponent& core) noexcept
{
    device = &dev;
    commands = &cmd;
    descriptors = &desc;
    coreCache = &core;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(location, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    if (scene == nullptr)
    {
        logger.consoleLog("Couldn't load model at location: ", UVK_LOG_TYPE_ERROR, location);
        std::terminate();
    }

    std::vector<UVK::FString> textureNames(scene->mNumMaterials);
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
        if (textureNames[i].empty() || !std_filesystem::exists(std_filesystem::path(textureNames[i].c_str())))
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
    Math::translate(model, { coreCache->translation.x + translationOffset.x, coreCache->translation.y + translationOffset.y, coreCache->translation.z + translationOffset.z });
    Math::rotate(model, { coreCache->rotation.x + rotationOffset.x, coreCache->rotation.y + rotationOffset.y, coreCache->rotation.z + rotationOffset.z });
    Math::scale(model, { coreCache->scale.x + scaleOffset.x, coreCache->scale.y + scaleOffset.y, coreCache->scale.z + scaleOffset.z });

    global.instance->initInfo.shaderPushConstant.data->model = model;
    global.instance->initInfo.shaderConstantStruct.data->normal = glm::mat4(glm::mat3(glm::inverse(glm::transpose(glm::mat3(model)))));
    global.instance->initInfo.shaderConstantStruct.data->ambientLightColour = global.ambientLight;

    auto& cmd = commands->getCommandBuffers()[currentImage];
    vkCmdPushConstants(cmd, pipeline.getPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, global.instance->initInfo.shaderPushConstant.size, global.instance->initInfo.shaderPushConstant.data);
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
        vertices[i].colour = hue;
        if (mesh->HasNormals())
            vertices[i].normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
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

void UVK::MeshComponent::saveToLevel(YAML::Emitter& out) noexcept
{
    out << YAML::Key << "mesh-model-location" << YAML::Value << loc;
    out << YAML::Key << "mesh-translation-offset" << YAML::Value << translationOffset;
    out << YAML::Key << "mesh-rotation-offset" << YAML::Value << rotationOffset;
    out << YAML::Key << "mesh-scale-offset" << YAML::Value << scaleOffset;
    out << YAML::Key << "mesh-hue" << YAML::Value << hue;
}

void UVK::MeshComponent::openFromLevel(UVK::Actor& act, const YAML::Node& entity) noexcept
{
    if (entity["mesh-model-location"] && entity["mesh-translation-offset"] && entity["mesh-rotation-offset"] && entity["mesh-scale-offset"] && entity["mesh-hue"])
    {
        auto& a = act.add<MeshComponent>();
        a.translationOffset = entity["mesh-translation-offset"].as<UVK::FVector>();
        a.rotationOffset = entity["mesh-rotation-offset"].as<UVK::FVector>();
        a.scaleOffset = entity["mesh-scale-offset"].as<UVK::FVector>();
        a.hue = entity["mesh-hue"].as<UVK::FVector4>();
        a.create(entity["mesh-model-location"].as<FString>().c_str(), global.renderer->device, global.renderer->commands, global.renderer->descriptors, act.get<UVK::CoreComponent>());
    }
}
