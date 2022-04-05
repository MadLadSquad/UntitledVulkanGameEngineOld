#pragma once

namespace UVK
{
    class Editor;
    class VKInstance;
    class VKDevice;
    class Commands;
    class VKDescriptors;
    class Swapchain;
    class GraphicsPipeline;

    class EditorUtilSettings
    {
    private:
        static void loadImGuiSettings(Editor& editor, const char* colTheme, VKInstance& instance, VKDevice& device, Commands& commands, VKDescriptors& descriptors, Swapchain& swapchain, GraphicsPipeline& graphicsPipeline) noexcept;
        static void setImGuiSettings(Editor& editor) noexcept;
        static void finishImGuiRender(Editor& editor) noexcept;
        friend class Editor;
    };
}