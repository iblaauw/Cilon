#pragma once

#include "Instruction.h"

class DuplicateInstruction : public Instruction
{
public:
    DuplicateInstruction() {}
    void Generate(Stream& out) const override;
};

