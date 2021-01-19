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
