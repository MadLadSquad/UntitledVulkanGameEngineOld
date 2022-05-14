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
	// A static string
	using String = const char*;
    // A dynamic string
	using FString = std::string;

	template<typename T>
	using EntityView = entt::view<T>;

    class Math;
    class Level;
}