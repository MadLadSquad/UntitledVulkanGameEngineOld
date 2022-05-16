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

        void createDescriptorSetLayout() noexcept;
        void destroyDescriptorSetLayout() noexcept;
        [[nodiscard]] const VkDescriptorSetLayout& layout() const noexcept;
        [[nodiscard]] const VkDescriptorSetLayout& samplerLayout() const noexcept;

        void createPushConstantRange() noexcept;
        [[nodiscard]] const VkPushConstantRange& getPushConstantRange() const noexcept;

        void createDescriptorPool() noexcept;
        void destroyDescriptorPool() noexcept;
        VkDescriptorPool& getPool() noexcept;

        void createDescriptorSets() noexcept;
        void destroyDescriptorSets() noexcept;
        [[nodiscard]] const std::vector<VkDescriptorSet>& getDescriptorSets() const noexcept;

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