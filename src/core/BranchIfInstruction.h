#pragma once

#include "Instruction.h"
#include "LabelInstruction.h"

class BranchIfInstruction : public Instruction
{
public:
    BranchIfInstruction(const LabelInstruction* label);
    BranchIfInstruction(const LabelInstruction* label, bool compareToTrue);

    void Generate(Stream& out) const override;

private:
    const LabelInstruction* label;
    bool compareToTrue;
};

