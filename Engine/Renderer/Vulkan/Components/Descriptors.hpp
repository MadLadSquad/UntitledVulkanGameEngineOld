#pragma once
#include "Device.hpp"
#include "Resources.hpp"

namespace UVK
{
    class VKDescriptors
    {
    public:
        VKDescriptors() = default;
        VKDescriptors(VKDevice& dev, Swapchain& swap, VKResources& res);

        // Create the descriptor set layout duh
        void createDescriptorSetLayout() noexcept;
        void destroyDescriptorSetLayout() noexcept;
        [[nodiscard]] const VkDescriptorSetLayout& layout() const noexcept;
        [[nodiscard]] const VkDescriptorSetLayout& samplerLayout() const noexcept;

        // Create the push constant range struct
        void createPushConstantRange() noexcept;
        [[nodiscard]] const VkPushConstantRange& getPushConstantRange() const noexcept;

        // Create the pool of descriptors
        void createDescriptorPool() noexcept;
        void destroyDescriptorPool() noexcept;
        VkDescriptorPool& getPool() noexcept;

        // Create the descriptor sets
        void createDescriptorSets() noexcept;
        void destroyDescriptorSets() noexcept;
        [[nodiscard]] const std::vector<VkDescriptorSet>& getDescriptorSets() const noexcept;

        // Create the descriptor for images
        size_t createTextureDescriptor(VkImageView imageView, const VkSampler& textureSampler) noexcept;
        void destroyTextureDescriptor();
        [[nodiscard]] const std::vector<VkDescriptorSet>& getSamplerDescriptorSets() const noexcept;
    private:
        friend class Swapchain;

        VkDescriptorSetLayout descriptorSetLayout{};
        VkDescriptorSetLayout samplerSetLayout{};

        VkDescriptorPool descriptorPool{};
        VkDescriptorPool samplerDescriptorPool{};

        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkDescriptorSet> samplerDescriptorSets;
        VkPushConstantRange pushConstantRange{};

        Swapchain* swapchain = nullptr;
        VKDevice* device = nullptr;
        VKResources* resources = nullptr;
    };
}