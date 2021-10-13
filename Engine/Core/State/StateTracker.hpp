// StateTracker.hpp
// Last update 13/10/2021 by Madman10K
#pragma once
#include <vector>
#include <cstdint>
#include <Core/Actor.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <GameFramework/Components/Components/MeshComponentRaw.hpp>
#include <GameFramework/Components/Components/MeshComponent.hpp>

namespace UVK
{
    class Actor;

    struct Transaction
    {
        std::function<void(UVK::Actor& ent, CoreComponent&, CoreComponent&, MeshComponentRaw&, MeshComponent&, bool*)> undofunc; // Called on undo
        std::function<void(UVK::Actor& ent, CoreComponent&, CoreComponent&, MeshComponentRaw&, MeshComponent&, bool*)> redofunc; // Called on redo
        Actor affectedEntity; // The entity that is going to be affected, can be empty
        CoreComponent coreComponent;
        CoreComponent deltaCoreComponent;
        MeshComponent meshComponent;
        MeshComponentRaw meshComponentRaw;
        bool bHasComponents[2];
    };

    /**
     * @brief Tracks state changes for the editor and actors. Handles things like Undo/Redo, stores states
     * of components and much more
     */
    class StateTracker
    {
    public:
        StateTracker() = default;
        StateTracker(const StateTracker&) = delete;
        void operator=(StateTracker const&) = delete;

        static void push(const Transaction& transaction);
        void init();
    private:
        friend class Editor;

        // Pushing adds a transaction to the transactions list and undo stack while also checking
        // if the transaction is within boundaries. If it isn't it starts overriding old transactions
        void pushAction(const Transaction& transaction);

        // Pops a transaction from the
        void undo();
        void redo();

        uint32_t transactionSize = 0;

        std::vector<Transaction*> undoStack;
        std::vector<Transaction*> redoStack;
        std::vector<Transaction> transactions;

        uint8_t transactionIndex = 0;
    };
}
