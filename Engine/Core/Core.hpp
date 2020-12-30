// Core.hpp
// Last update 12/7/2020 by Stanislav Vasilev(Madman10K)
#pragma once

// Includes
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/mat3x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../ThirdParty/entt/src/entt/entt.hpp"
#include <yaml-cpp/yaml.h>
#include <UVKLog.h>

// Types
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

// Defines
// Asset Defines
#define UVK_MODEL_ASSET 0
#define UVK_AUDIO_ASSET 1
#define UVK_SHADER_ASSET 2
#define UVK_TEXTURE_ASSET 3
#define UVK_LEVEL_ASSET 4
#define UVK_API

class Utility
{
public:
    const char* toLower(const char* str)
    {
        auto string = static_cast<std::string>(str);

        std::transform(string.begin(), string.end(), string.begin(), ::tolower);

        return string.c_str();
    }

    const char* toHigher(const char* str)
    {
        auto string = static_cast<std::string>(str);

        std::transform(string.begin(), string.end(), string.begin(), ::toupper);

        return string.c_str();
    }
};





