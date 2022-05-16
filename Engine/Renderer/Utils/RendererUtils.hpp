#pragma once


namespace UVK
{
    // A struct containing the renderer settings
    struct UVK_PUBLIC_API RendererSettings
    {
        RendererSettings() = default;
        FString themeLoc;
        bool bVsync = false;
        bool bVsyncImmediate = true;
        uint32_t samples = VK_SAMPLE_COUNT_1_BIT;
        bool sampleRateShading = false;
        float sampleRateShadingMult = 0.25f;

        void saveSettings() const noexcept;
    };

    struct UVK_PUBLIC_API ShaderConstantBase
    {
        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 normal;
        glm::mat4 inverseViewMatrix{1.0f};

        glm::vec4 lightPosition = { 0.0f, 0.75f, -5.0f, 0.0f };
        glm::vec4 lightColour = { 1.0f, 1.0f, 1.0f, 1.0f };
        glm::vec4 ambientLightColour = { 0.0f, 0.0f, 0.0f, 0.0f };
    };

    struct UVK_PUBLIC_API ShaderPushConstantBase
    {
        glm::mat4 model;
    };

    // A struct of values that will be constant for all shaders, they can still be changed from frame to frame but will not be different for every shader that uses them
    struct UVK_PUBLIC_API ShaderConstantStruct
    {
        ShaderConstantBase* data = nullptr;
        size_t size = 0;
    };

    // A struct of mutable values of bigger size than 128bits
    struct UVK_PUBLIC_API ShaderMutableStruct
    {
        void* data = nullptr;
        size_t size = 0;

        std::function<void(void*)> updateDynamicUniformBufferCallback = [](void*) {};
    };

    // A struct of mutable values of max size of 128 bits, 64bits occupied by the model struct
    struct UVK_PUBLIC_API ShaderPushConstant
    {
        ShaderPushConstantBase* data = nullptr;
        uint8_t size = 0;
    };
}