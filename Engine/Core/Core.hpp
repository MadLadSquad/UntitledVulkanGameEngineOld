// Core.hpp
// Last update 12/7/2020 by Stanislav Vasilev(Madman10K)

// Includes
#include <vector>
#include <map>
#include <unordered_map>
#include <hash_map>
#include <queue>
#include <iostream>
#include <cstdio>
#include <string>
#include <glm/glm.hpp>
#include <glm/mat3x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt.hpp>

// Types
// Array
template<typename T>
using TArray = std::vector<T>;
// Model matrix
typedef glm::mat4 Model;
// Vector3
typedef glm::vec3 FVector;
// Entity Pool owns and manages all the entities
typedef entt::registry EntityPool;
// Entity
typedef entt::entity Actor;
// String
using String = const char*;

// Defines
// Asset Defines
#define UVK_MODEL_ASSET 0
#define UVK_AUDIO_ASSET 1
#define UVK_SHADER_ASSET 2
#define UVK_TEXTURE_ASSET 3
#define UVK_LEVEL_ASSET 4

#define UVK_API