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

        /**
         * @brief Create the uniform buffers
         * @param dependencySizeLink - Make 1:1 proportional sizing with things like the framebuffers
         */
        void createUniformBuffers(size_t dependencySizeLink) noexcept;
        /**
         * @brief Updates the buffer content
         * @param mvp - The MVP struct to be pushed every frame
         * @param imageIndex - The image index from the commands
         */
        void updateUniformBuffers(VP& mvp, uint32_t imageIndex) noexcept;
        void destroyUniformBuffers() noexcept;
        std::vector<VKBuffer>& getUniformBuffers() noexcept;

        // Allocate memory for the dynamic uniform buffers
        void allocateDynamicUniformBufferTransferSpace() noexcept;
        void freeDynamicUniformBufferTransferSpace() noexcept;
        std::vector<VKBuffer>& getDynamicUniformBuffers() noexcept;
        size_t& getModelUniformAlignment() noexcept;
    private:
        VKDevice* device = nullptr;

        void* modelTransferSpace;
        size_t modelUniformAlignment;

        std::vector<VKBuffer> uniformBuffers;
        std::vector<VKBuffer> dynamicUniformBuffers;
    };
}