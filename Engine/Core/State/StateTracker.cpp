// StateTracker.cpp
// Last update 19/10/2021 by Madman10K
#include "StateTracker.hpp"
#include <Core/Actor.hpp>
#include <Renderer/EditorUI/Editor.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>

void UVK::StateTracker::pushAction(const UVK::Transaction& transaction)
{
    if (transactions.size() == transactionSize)
    {
        // Destroying half of the buffer saves memory and performance for future transactions
        for (uint32_t i = 0; i < (transactionSize/2); i++)
        {
            for (auto& a : undoStack)
            {
                if (&transactions[i] == a)
                {
                    a = nullptr; // Set "a" to nullptr for safety idk
                    // This is bad, very, very bad, although most users won't set the limit very high
                    for (auto& b : undoStack)
                    {
                        if (&b == &a)
                        {
                            undoStack.pop_front();
                            break;
                        }
                        undoStack.pop_front();
                    }
                }
            }
            for (auto& a : redoStack)
            {
                if (&transactions[i] == a)
                {
                    a = nullptr; // Set "a" to nullptr for safety idk
                    // This is bad, very, very bad, although most users won't set the limit very high
                    for (auto& b : redoStack)
                    {
                        if (&b == &a)
                        {
                            redoStack.pop_front();
                            break;
                        }
                        redoStack.pop_front();
                    }
                }
            }
            transactions.pop_front();
        }
    }
    transactions.push_back(transaction);
    undoStack.push_back(&transactions.back());
}

void UVK::StateTracker::undo()
{
    if (!undoStack.empty())
    {
        redoStack.emplace_back(undoStack.back());
        undoStack.back()->undofunc(redoStack.back()->transactionPayload);

        undoStack.pop_back();
    }
}

void UVK::StateTracker::redo()
{
    if (!redoStack.empty())
    {
        undoStack.emplace_back(redoStack.back());
        redoStack.back()->redofunc(redoStack.back()->transactionPayload);

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
}
