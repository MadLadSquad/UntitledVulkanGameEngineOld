// StateTracker.hpp
// Last update 18/2/2022 by Madman10K
#pragma once
#include <vector>
#include <cstdint>
#include <Core/Actor.hpp>
#include <deque>
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <GameFramework/Components/Components/MeshComponentRaw.hpp>
#include <GameFramework/Components/Components/MeshComponent.hpp>
#include <GameFramework/Components/Components/AudioComponent.hpp>

namespace UVK
{
    class Actor;

    struct UVK_PUBLIC_API TransactionPayload
    {
        Actor affectedEntity; // The entity that is going to be affected, can be empty
        CoreComponent coreComponent;
        CoreComponent deltaCoreComponent;
        MeshComponent meshComponent;
        MeshComponentRaw meshComponentRaw;
        AudioComponent audioComponent;
        bool bHasComponents[3];
        bool* bChanged = nullptr;
        volatile bool* vbChanged = nullptr;
        std_filesystem::path* path = nullptr;
    };

    struct UVK_PUBLIC_API Transaction
    {
        ~Transaction()
        {
            undofunc = [](TransactionPayload&){};
            redofunc = [](TransactionPayload&){};
            transactionPayload.deltaCoreComponent.name.clear();
            transactionPayload.deltaCoreComponent.devName.clear();
            transactionPayload.coreComponent.id = 0;
            transactionPayload.coreComponent.name.clear();
            transactionPayload.coreComponent.devName.clear();
            transactionPayload.coreComponent.id = 0;
            transactionPayload.meshComponentRaw.clearMesh();
            transactionPayload.meshComponent.clearMesh();
        }
        std::function<void(TransactionPayload&)> undofunc; // Called on undo
        std::function<void(TransactionPayload&)> redofunc; // Called on redo
        TransactionPayload transactionPayload;
    };
    /**
     * @brief Tracks state changes for the editor and actors. Handles things like Undo/Redo, stores states
     * of components and much more
     */
    class UVK_PUBLIC_API StateTracker
    {
    public:
        StateTracker() = default;
        StateTracker(const StateTracker&) = delete;
        void operator=(StateTracker const&) = delete;

        static void push(const Transaction& transaction);
        void init();
    private:
        friend class EditorGUIUtils;

        // Pushing adds a transaction to the transactions list and undo stack while also checking
        // if the transaction is within boundaries. If it isn't it starts overriding old transactions
        void pushAction(const Transaction& transaction);

        // Pops a transaction from the
        void undo();
        void redo();

        uint32_t transactionSize = 0;

        std::deque<Transaction*> undoStack;
        std::deque<Transaction*> redoStack;
        std::deque<Transaction> transactions;

        uint8_t transactionIndex = 0;
    };
}
