// StateTracker.hpp
// Last update 22/9/2021 by Madman10K
#pragma once
#include <vector>
#include <cstdint>

namespace UVK
{
    class Actor;

    struct Transaction
    {
        std::function<void(void)> undofunc; // Called on undo
        std::function<void(void)> redofunc; // Called on redo
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

        static void addTransaction(const Transaction& transaction);
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
