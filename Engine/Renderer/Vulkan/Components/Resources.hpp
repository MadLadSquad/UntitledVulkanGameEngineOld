#pragma once
#include "VKMesh.hpp"
#include <vector>

namespace UVK
{
    class VKResources
    {
    public:
        VKResources() = default;
        explicit VKResources(VKDevice& dev) noexcept;

        void createUniformBuffers(size_t dependencySizeLink) noexcept;
        void updateUniformBuffers(VP& mvp, uint32_t imageIndex) noexcept;
        void destroyUniformBuffers() noexcept;
        std::vector<VKBuffer>& getUniformBuffers() noexcept;

        void allocateDynamicUniformBufferTransferSpace() noexcept;
        void freeDynamicUniformBufferTransferSpace() noexcept;
    private:
        VKDevice* device = nullptr;

        std::vector<VKBuffer> uniformBuffers;
        std::vector<VKBuffer> dynamicUniformBuffers;
    };
}