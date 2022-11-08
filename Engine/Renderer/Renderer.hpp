#pragma once
#include <Core/Defines.hpp>

namespace UVK
{
    class Level;
    struct RendererSettings;
    /**
     * @brief Manages the currently used renderer and can switch renderers
     */
    class UVK_PUBLIC_API RendererInternal
    {
    public:
        RendererInternal() = delete;
        RendererInternal(const RendererInternal&) = delete;
        void operator=(RendererInternal const&) = delete;
        RendererInternal(UVK::Level* lvl, bool bUsesEditor) noexcept;
    private:
        friend class Editor;

        void loadSettings() noexcept;
        void startRenderer(UVK::Level* lvl, bool bUsesEditor) noexcept;

        RendererSettings* rs{};
    };
}