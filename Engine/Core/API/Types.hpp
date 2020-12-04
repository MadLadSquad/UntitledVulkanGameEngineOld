#include "Defines.h"

using String = const char*;
using FString = std::string;
template<typename T, size_t size>
using Array = std::array<T, size>;
template<typename T>
using TArray = std::vector<T>;
template<typename Key, typename Value>
using TMap = std::map<Key, Value>;
template<typename Key, typename Value>
using THashMap = std::unordered_map<Key, Value>;
using Actor = entt::entity;
using Container = entt::registry;
typedef glm::mat4 Model;
typedef glm::vec3 FVector;