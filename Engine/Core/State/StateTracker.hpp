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


    /**
     * @brief The transaction payload struct provides a bunch of data types that can be used with the Undo/Redo system
     * @var affectedEntity - The entity that is going to be affected by the transaction
     * @var coreComponent - The original core component struct for the entity
     * @var deltaCoreComponent - An intermediate core component for the entity
     * @var meshComponent - A mesh component for the entity
     * @var meshComponentRaw - A raw mesh component for the entity
     * @var audioComponent - An audio component for the entity
     * @var bHasComponents - An array of booleans where each index corresponds to a different component, specified in the ComponentTypes enum
     * @var bChanged - A pointer to a bChanged boolean
     * @var vbChanged - A volatile pointer to a bChanged boolean
     * @var path - An std::filesystem::path pointer
     */
    struct UVK_PUBLIC_API TransactionPayload
    {
        enum ComponentTypes
        {
            COMPONENT_MESH_RAW = 0,
            COMPONENT_MESH = 0,
            COMPONENT_AUDIO = 2
        };
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

    /**
     * @brief The transaction struct contains all information related to an Undo/Redo transaction
     * @var undofunc - A callback function to be called on undo, requires a TransactionPayload& as an argument
     * @var redofunc - A callback function to be called on redo, requires a TransactionPayload& as an argument
     * @var transactionPayload - The actual transaction payload to be passed into those functions
     */
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
            transactionPayload.meshComponentRaw.destroy();
            transactionPayload.meshComponent.destroy();
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

        // Pushes a transaction to the transactions list
        static void push(const Transaction& transaction) noexcept;
        // Initializes the struct
        void init() noexcept;
    private:
        friend class EditorGUIUtils;

        // Pushing adds a transaction to the transactions list and undo stack while also checking
        // if the transaction is within boundaries. If it isn't it starts overriding old transactions
        void pushAction(const Transaction& transaction) noexcept;

        // Pops a transaction from the
        void undo() noexcept;
        void redo() noexcept;

        uint32_t transactionSize = 0;

        // A deque of Transaction* for undo, references all transactions that can be undone
        std::deque<Transaction*> undoStack;
        // A deque of Transaction* for redo, references all transactions that can be redone
        std::deque<Transaction*> redoStack;
        // A deque of Transactions that contains the full list of them
        std::deque<Transaction> transactions;

        uint8_t transactionIndex = 0;
    };
}
