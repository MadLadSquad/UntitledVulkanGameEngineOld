// VKGraphicsPipeline.hpp
// Last update 1/8/2021 by Madman10K
#pragma once

namespace UVK
{
    /**
     * @brief A Vulkan graphics pipeline manager
     */
    class VKGraphicsPipeline
    {
    public:
        void create();
        void destroy();

    private:
        void createVertextShaderStage();
    };
}