#pragma once

#include "Instruction.h"
#include "StackState.h"
#include "LabelInstruction.h"

class BasicBlock
{
public:
    BasicBlock(Identifier name);
private:
    BasicBlock(Identifier name, const StackState& state);

public:
    void Add(std::unique_ptr<Instruction> instr, std::vector<ILType*> args, ILType* result);

    void Branch(BasicBlock* block);
    void BranchCompare(BasicBlock* blockTrue, BasicBlock* blockFalse);
    void BranchIf(BasicBlock* blockTrue, BasicBlock* blockFalse);

    void Return(ILType* retType);

    void Lock() noexcept;

    std::unique_ptr<BasicBlock> CreateChildBlock(Identifier name) const;

    const LabelInstruction& GetStartLabel() const { return *startLabel; }

private:
    void IsLockedGuard() const;
    void NotBranchedGuard() const;
    void RaiseStackMismatch() const;

    const StackState startStack;
    StackState currentStack;

    std::vector<std::unique_ptr<Instruction>> instructions;

    LabelInstruction* startLabel;

    BasicBlock* targetBlock;
    BasicBlock* targetBlock2;

    bool isLocked;
    bool isBranched;
};

