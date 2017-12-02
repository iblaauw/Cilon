#include "BasicBlock.h"

#include "Exceptions.h"
#include "ReturnInstruction.h"
#include "BranchInstruction.h"
#include "BranchIfInstruction.h"

BasicBlock::BasicBlock(Identifier name)
    : startStack(), currentStack()
{
    std::unique_ptr<LabelInstruction> label = std::make_unique<LabelInstruction>(name);
    startLabel = label.get();
    instructions.emplace_back(std::move(label));
}

BasicBlock::BasicBlock(Identifier name, const StackState& state)
    : startStack(state), currentStack(state)
{
    std::unique_ptr<LabelInstruction> label = std::make_unique<LabelInstruction>(name);
    startLabel = label.get();
    instructions.emplace_back(std::move(label));
}

void BasicBlock::Add(std::unique_ptr<Instruction> instr, std::vector<ILType*> args, ILType* result)
{
    if (isLocked)
        throw InvalidOperationException("Cannot add an instruction: the basic block is locked.");

    instructions.emplace_back(std::move(instr));
    currentStack.Transition(args, result);
}

void BasicBlock::Branch(BasicBlock* block)
{
    IsLockedGuard();
    NotBranchedGuard();

    if (block == nullptr)
        throw NullArgumentException("'block' cannot be null");

    if (block == this)
        throw InvalidOperationException("Infinite loop detected: basic block attempting to branch to itself.");

    if (!currentStack.Matches(block->startStack))
        RaiseStackMismatch();

    targetBlock = block;
    auto* targetLabel = block->startLabel;
    instructions.emplace_back(std::make_unique<BranchInstruction>(targetLabel));
    isBranched = true;
}

void BasicBlock::BranchIf(BasicBlock* blockTrue, BasicBlock* blockFalse)
{
    IsLockedGuard();
    NotBranchedGuard();

    if (blockTrue == nullptr || blockFalse == nullptr)
        throw NullArgumentException("Argument cannot be null");

    // TODO: verify top of stack has corect type
    currentStack.Pop();

    if (!currentStack.Matches(blockTrue->startStack)
        || !currentStack.Matches(blockFalse->startStack))
        RaiseStackMismatch();

    targetBlock = blockTrue;
    targetBlock2 = blockFalse;

    auto* targetLabel = blockTrue->startLabel;
    instructions.emplace_back(std::make_unique<BranchIfInstruction>(targetLabel));
    isBranched = true;
}

void BasicBlock::Return(ILType* retType)
{
    IsLockedGuard();
    NotBranchedGuard();

    if (retType == nullptr)
        throw NullArgumentException("'retType' cannot be null");

    if (retType == ILType::GetVoid())
    {
        if (currentStack.Pop() != nullptr)
            RaiseStackMismatch();
    }
    else if (!currentStack.MatchesTop({ retType }))
    {
        RaiseStackMismatch();
    }

    instructions.emplace_back(std::make_unique<ReturnInstruction>());
    isBranched = true;
}

void BasicBlock::Lock() noexcept
{
    isLocked = true;
}

std::unique_ptr<BasicBlock> BasicBlock::CreateChildBlock(Identifier name) const
{
    IsLockedGuard();
    std::unique_ptr<BasicBlock> child ( new BasicBlock(name, currentStack) );
    return child;
}

void BasicBlock::IsLockedGuard() const
{
    if (!isLocked)
        throw InvalidOperationException("The BasicBlock must be locked before calling this method");
}

void BasicBlock::NotBranchedGuard() const
{
    if (!isBranched)
        throw InvalidOperationException("The BasicBlock already has a branch target set");
}

void BasicBlock::RaiseStackMismatch() const
{
        throw InvalidOperationException("Cannot branch to target basic block: mismatch between the current stack and the target block starting stack.");
}


