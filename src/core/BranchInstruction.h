#pragma once

#include "Instruction.h"
#include "LabelInstruction.h"

class BranchInstruction : public Instruction
{
public:
    BranchInstruction(const LabelInstruction* label);

    void Generate(Stream& out) const override;

private:
    const LabelInstruction* label;
};

