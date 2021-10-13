// StateTracker.cpp
// Last update 13/10/2021 by Madman10K
#include "StateTracker.hpp"
#include <Core/Actor.hpp>
#include <Renderer/EditorUI/Editor.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>

void UVK::StateTracker::pushAction(const UVK::Transaction& transaction)
{
    if (transactionIndex == transactionSize)
    {
        // We go back 6 six times since we are erasing 5 elements and transactionSize is the size of the
        // transaction array + 1
        transactionIndex = transactionSize - 6;

        for (int i = 0; i < undoStack.size(); i++)
        {
            // For efficiency's sake we remove 5 elements instead of one
            // meaning that the max transaction size should always be above 4
            if (undoStack[i] == &transactions[0] || undoStack[i] == &transactions[1] || undoStack[i] == &transactions[2] || undoStack[i] == &transactions[3] || undoStack[i] == &transactions[4])
                undoStack.erase(undoStack.begin() + i);
        }

        for (int i = 0; i < redoStack.size(); i++)
        {
            // For efficiency's sake we remove 5 elements instead of one
            // meaning that the max transaction size should always be above 4
            if (redoStack[i] == &transactions[0] || redoStack[i] == &transactions[1] || redoStack[i] == &transactions[2] || redoStack[i] == &transactions[3] || redoStack[i] == &transactions[4])
                redoStack.erase(redoStack.begin() + i);
        }

        for (uint8_t i = 0; i < 5; i++)
        {
            transactions[i].affectedEntity.destroy();
        }
        transactions.erase(transactions.begin(), transactions.begin() + 4);
    }

    transactions[transactionIndex] = transaction;
    undoStack.emplace_back(&transactions[transactionIndex]);

    transactionIndex++;
}

void UVK::StateTracker::undo()
{
    if (!undoStack.empty())
    {
        redoStack.emplace_back(undoStack.back());
        undoStack.back()->undofunc(redoStack.back()->affectedEntity, redoStack.back()->coreComponent, redoStack.back()->deltaCoreComponent, redoStack.back()->meshComponentRaw, redoStack.back()->meshComponent, redoStack.back()->bHasComponents);

        undoStack.pop_back();
    }
}

void UVK::StateTracker::redo()
{
    if (!redoStack.empty())
    {
        undoStack.emplace_back(redoStack.back());
        redoStack.back()->redofunc(redoStack.back()->affectedEntity, redoStack.back()->coreComponent, redoStack.back()->deltaCoreComponent, redoStack.back()->meshComponentRaw, redoStack.back()->meshComponent, redoStack.back()->bHasComponents);

        redoStack.pop_back();
    }
}

void UVK::StateTracker::push(const UVK::Transaction& transaction)
{
    global.instance->stateTracker.pushAction(transaction);
}

void UVK::StateTracker::init()
{
    transactionSize = global.rendererSettings.maxSavedTransactions;
    transactions.resize(transactionSize);
}
