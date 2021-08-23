// VKDescriptorSets.hpp
// Last update 22/8/2021 by Madman10K
#pragma once
#ifndef __APPLE__
#include <vulkan/vulkan.h>
#include <vector>

namespace UVK
{
    class VKDevice;
    class VKSwapchain;

    class VKDescriptorSets
    {
    public:
        VKDescriptorSets() = default;
        VKDescriptorSets(VKDevice& dev, VKSwapchain& swap);

        void createDescriptorSetLayout();
        void destroyDescriptorSetLayout();

        void createUniformBuffers();
        void createDescriptorPool();
        void createDescriptorSets();

        VkDescriptorSetLayout& layout();
        const std::vector<VkDescriptorSet>& getDescriptorSets();
    private:
        VkDescriptorSetLayout descriptorSetLayout{};
        VkDescriptorPool descriptorPool{};

        VKDevice* device{};
        VKSwapchain* swapchain{};

        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBufferMemory;
    };
}
#endif