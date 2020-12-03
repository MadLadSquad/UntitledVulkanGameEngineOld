#include <iostream> 
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <thread>
#include "../../ThirdParty/EnTT/entt.hpp"
#include "../../ThirdParty/glm/glm/glm.hpp"
#include "../../ThirdParty/glm/glm/mat4x4.hpp"
#include "../../ThirdParty/glm/glm/gtc/matrix_transform.hpp"
#include "../../ThirdParty/glm/glm/gtc/type_ptr.hpp"

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