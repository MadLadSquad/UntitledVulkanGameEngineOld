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
        // Load ImGui settings and initialize the editor and ImGui
        static void loadImGuiSettings(Editor& editor, const char* colTheme, InternalRendererComponents& renderer) noexcept;
        // Set the ImGui settings when rendering a new frame
        static void setImGuiSettings(Editor& editor) noexcept;
        // The code to be called when an ImGui frame finishes rendering
        static void finishImGuiRender(Editor& editor, uint32_t currentImage) noexcept;
        friend class Editor;
    };
}