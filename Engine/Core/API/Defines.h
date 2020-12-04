#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <thread>
#include "../../ThirdParty/EnTT/entt.hpp"
#include "../../ThirdParty/GLM/glm/glm.hpp"
#include "../../ThirdParty/GLM/glm/mat4x4.hpp"
#include "../../ThirdParty/GLM/glm/gtc/matrix_transform.hpp"
#include "../../ThirdParty/GLM/glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include <iostream>
#define LOG(x, ...) printf(x, __VA_ARGS__);
#ifdef GAME
	#define UVK_API
#else
	#define UVK_API
#endif
#define Legacy

