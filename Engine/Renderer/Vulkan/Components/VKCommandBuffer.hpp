#pragma once
#ifndef __APPLE__
#include <vulkan/vulkan.h>

namespace UVK
{
	class VKCommandBuffer
	{
	public:
		VKCommandBuffer() = default;


	private:
		VkCommandBuffer commandBuffer;
	};
}

#endif