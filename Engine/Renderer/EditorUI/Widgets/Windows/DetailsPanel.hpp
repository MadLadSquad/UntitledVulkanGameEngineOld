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
    bool DrawVec3Control(const UVK::FString& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f, float speed = 1.0f) noexcept;

    template<typename T>
    void addComponent(UVK::Actor& ent) noexcept
    {
        if (!ent.has<T>())
        {
            ent.add<T>();

            UVK::Transaction transaction =
            {
                .undofunc = [](UVK::TransactionPayload& payload)
                {
                    if (payload.affectedEntity.has<T>())
                        payload.affectedEntity.remove<T>();
                },
                .redofunc = [](UVK::TransactionPayload& payload)
                {
                    if (payload.affectedEntity.has<T>())
                        payload.affectedEntity.add<T>();
                },
                .transactionPayload =
                {
                    .affectedEntity = ent
                }
            };

            UVK::StateTracker::push(transaction);
        }
    }

    template<typename T>
    void removeComponent(UVK::Actor& ent) noexcept
    {
        if (ent.has<T>())
        {
            ent.remove<T>();

            UVK::Transaction transaction =
            {
                .undofunc = [](UVK::TransactionPayload& payload)
                {
                    if (payload.affectedEntity.has<T>())
                        payload.affectedEntity.add<T>();
                },
                .redofunc = [](UVK::TransactionPayload& payload)
                {
                    if (payload.affectedEntity.has<T>())
                        payload.affectedEntity.remove<T>();
                },
                .transactionPayload =
                {
                    .affectedEntity = ent
                }
            };

            UVK::StateTracker::push(transaction);
        }
    }

    bool display(UVK::Actor& ent, UVK::Level* lvl, bool& bShow, const UVK::EditorModuleManager& modules, bool& destroy) noexcept;
}
#endif