// VulkanRenderer.hpp
// Last update 1/20/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <vulkan.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class VulkanRenderer
{
public:
    void start();

private:

    VkInstance instance;
    void createInstance();
    bool checkExtensionSupport(std::vector<const char*>* extensions);
};
