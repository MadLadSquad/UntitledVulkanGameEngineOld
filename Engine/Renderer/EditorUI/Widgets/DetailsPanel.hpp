// DetailsPanel.hpp
// Last update 13/10/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef PRODUCTION
#include <Renderer/Textures/Texture.hpp>
#include <Core/Actor.hpp>
#include <State/StateTracker.hpp>

namespace UVK
{
    class Level;
    class EditorModuleManager;
}
/**
 * @brief Displays the Details Panel which is used to add, manipulate and remove components from selected entities
 */
namespace DetailsPanel
{
    // All of this is copied from the Cherno because his styling looks great
    bool DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);

    template<typename T>
    void addComponent(UVK::Actor& ent)
    {
        if (!ent.has<T>())
        {
            ent.add<T>();

            UVK::Transaction transaction =
            {
                .undofunc = [](UVK::Actor& en, UVK::CoreComponent&, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                {
                    if (en.has<T>())
                        en.remove<T>();
                },
                .redofunc = [](UVK::Actor& en, UVK::CoreComponent&, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                {
                    if (en.has<T>())
                        en.add<T>();
                },
                .affectedEntity = ent
            };

            UVK::StateTracker::push(transaction);
        }
    }

    template<typename T>
    void removeComponent(UVK::Actor& ent)
    {
        if (ent.has<T>())
        {
            ent.remove<T>();

            UVK::Transaction transaction =
            {
                .undofunc = [](UVK::Actor& en, UVK::CoreComponent&, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                {
                    if (en.has<T>())
                        en.add<T>();
                },
                .redofunc = [](UVK::Actor& en, UVK::CoreComponent&, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                {
                    if (en.has<T>())
                        en.remove<T>();
                },
                .affectedEntity = ent
            };

            UVK::StateTracker::push(transaction);
        }
    }

    void display(UVK::Actor& ent, UVK::Level* lvl, bool& bShow, const UVK::EditorModuleManager& modules, bool& destroy);
}
#endif