#pragma once

#include "Instruction.h"
#include "LabelInstruction.h"
#include "Comparison.h"

class BranchCompareInstruction : public Instruction
{
public:
    BranchCompareInstruction(const LabelInstruction* label, FullComparison comparison);
    BranchCompareInstruction(const LabelInstruction* label, Comparison comparison);

    void Generate(Stream& out) const override;

private:
    const char* ComparisonToString() const;

    const LabelInstruction* label;
    FullComparison comparison;
};

