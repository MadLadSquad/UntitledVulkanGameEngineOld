#pragma once
#include "../../Core/API/Defines.h"
#ifndef Legacy
#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>

namespace UVK
{
	class UVK_API VkRenderer
	{
	public:
		int InitWindow();
	};
}
#endif

