#include "StateTracker.hpp"
#include <Core/Actor.hpp>
#include <Renderer/EditorUI/Editor.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>

void UVK::StateTracker::pushAction(const UVK::Transaction& transaction) noexcept
{
    if (transactions.size() == transactionSize)
    {
        // Destroying half of the buffer saves memory and performance for future transactions
        for (uint32_t i = 0; i < (transactionSize/2); i++)
        {
            for (int j = 0; j < undoStack.size(); j++)
            {
                if (&transactions[i] == undoStack[j])
                {
                    undoStack[j] = nullptr;
                    for (int m = 0; m <= j; m++)
                        undoStack.pop_front();
                }
            }

            for (int j = 0; j < redoStack.size(); j++)
            {
                if (&transactions[i] == redoStack[j])
                {
                    redoStack[j] = nullptr;
                    for (int m = 0; m <= j; m++)
                        redoStack.pop_front();
                }
            }

            transactions.pop_front();
        }
    }
    transactions.push_back(transaction);
    undoStack.push_back(&transactions.back());
}

void UVK::StateTracker::undo() noexcept
{
    if (!undoStack.empty())
    {
        redoStack.emplace_back(undoStack.back());
        undoStack.back()->undofunc(redoStack.back()->transactionPayload);

        undoStack.pop_back();
    }
}

void UVK::StateTracker::redo() noexcept
{
    if (!redoStack.empty())
    {
        undoStack.emplace_back(redoStack.back());
        redoStack.back()->redofunc(redoStack.back()->transactionPayload);

        redoStack.pop_back();
    }
}

void UVK::StateTracker::push(const UVK::Transaction& transaction) noexcept
{
    global.instance->stateTracker.pushAction(transaction);
}

void UVK::StateTracker::init() noexcept
{
    transactionSize = global.instance->editor->settings.maxSavedTransactions;
}
