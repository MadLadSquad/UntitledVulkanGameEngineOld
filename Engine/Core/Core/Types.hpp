#pragma once
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <vector>
#include <glm/glm.hpp>
#include "Engine/ThirdParty/entt/src/entt/entt.hpp"
#include <yaml-cpp/yaml.h>

namespace UVK
{
	// Vector3
	typedef glm::vec3 FVector;
	// Vector4
	typedef glm::vec4 FVector4;
	// Vector2
	typedef glm::vec2 FVector2;
	// Entity Pool owns and manages all the entities
	typedef entt::registry EntityPool;
	// String
	using String = const char*;

	using FString = std::string;

	template<typename T>
	using EntityView = entt::view<T>;

    class Math;
    class Level;

    struct FilesystemWidgetData
    {
        float padding = 20.0f;
        float imageSize = 50.0f;
        uint32_t maxFileNum = 64;
        bool bUsePreviews = false;
    };
}