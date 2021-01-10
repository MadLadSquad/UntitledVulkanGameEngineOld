// Types.hpp
// Last update 1/10/2021 by Madman10K
#include <vector>
#include <glm/glm.hpp>
#include <glm/mat3x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/ThirdParty/entt/src/entt/entt.hpp"

// Array
template<typename T>
using TArray = std::vector<T>;
// Model matrix
typedef glm::mat4 Model;
// Vector3
typedef glm::vec3 FVector;
// Vector4
typedef glm::vec4 FVector4;
// Entity Pool owns and manages all the entities
typedef entt::registry EntityPool;
// Entity
typedef entt::entity Actor;
// String
using String = const char*;
