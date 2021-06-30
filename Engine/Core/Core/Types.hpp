// Types.hpp
// Last update 30/6/2021 by Madman10K
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <vector>
#include <glm/glm.hpp>
#include <glm/mat3x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/ThirdParty/entt/src/entt/entt.hpp"

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

    class Math;
}