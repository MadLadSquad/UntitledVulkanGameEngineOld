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
    class InternalRendererComponents;

    class EditorUtilSettings
    {
    private:
        static void loadImGuiSettings(Editor& editor, const char* colTheme, InternalRendererComponents& renderer) noexcept;
        static void setImGuiSettings(Editor& editor) noexcept;
        static void finishImGuiRender(Editor& editor, uint32_t currentImage) noexcept;
        friend class Editor;
    };
}