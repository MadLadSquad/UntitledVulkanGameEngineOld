#pragma once
#include "Device.hpp"

namespace UVK
{
    /**
     * @brief A utility class to simplify Vulkan buffer operations
     */
    class VKBuffer
    {
    public:
        /**
         * @brief Creates a generic Vulkan buffer
         * @param dev - A reference to the device class that contains both our physical and logical devices
         * @param bufferSize - The size of the buffer
         * @param bufferUsageFlags - The specific flags for how the buffer is going to be used
         * @param propertyFlags - The memory flags specifying its properties
         */
        void create(VKDevice& dev, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags propertyFlags) noexcept;
        // Destroys the buffer
        void destroy() noexcept;

        /**
         * @brief Given a transfer queue, transfer command pool and a reference to a buffer, will copy the data in the buffer calling this function to the buffer specified as an argument, using a transfer command buffer.
         * @param transferQueue - The specified transfer queue. The vulkan spec defines the transfer queue as the graphics queue, so you should pass that here
         * @param transferCommandPool - The command pool to be used
         * @param buf - The buffer to get the information copied to
         */
        void copy(VkQueue transferQueue, VkCommandPool transferCommandPool, VKBuffer& buf) noexcept;
        /**
         * @brief Same as the copy function, but for images
         * @param image - The image to be copied to
         * @param size - The size of the image as a 2D vector
         */
        void copyImageBuffer(VkQueue transferQueue, VkCommandPool transferCommandPool, VkImage image, FVector2 size) noexcept;

        // A utility function to start the transfer command buffer
        static VkCommandBuffer beginCommandBuffer(VkCommandPool transferCommandPool, VKDevice& device) noexcept;
        // A utility function to end the transfer command buffer
        static void endCommandBuffer(VkQueue transferQueue, VkCommandPool& transferCommandPool, VkCommandBuffer& transferCommandBuffer, VKDevice& device) noexcept;

       /**
        * @brief Enables transitioning of an image layout to a new one
        * @param queue - The transfer queue, mostly the graphics queue will be used here
        * @param commandPool - The command pool to execute the commands
        * @param image - The image to be transitioned
        * @param old - The old layout of the image
        * @param newl - The new layout of the image
        * @param mipLevels - The mip levels of the image
        */
        void transitionImageLayout(const VkQueue& queue, VkCommandPool& commandPool, const VkImage& image, VkImageLayout old, VkImageLayout newl, uint32_t mipLevels = 1) noexcept;

        // Returns the memory size of the buffer
        VkDeviceMemory& getMemory() noexcept;
        // Returns the raw Vulkan buffer object handle
        VkBuffer& getBuffer() noexcept;
    private:
        VkBuffer buffer{};
        VkDeviceMemory memory{};
        VkDeviceSize bufferSz{};

        VKDevice* device = nullptr;
        uint32_t findMemoryTypeIndex(uint32_t allowedTypes, VkMemoryPropertyFlags properties) noexcept;
    };
}