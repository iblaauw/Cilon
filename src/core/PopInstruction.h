#pragma once

#include "Instruction.h"

class PopInstruction : public Instruction
{
public:
    PopInstruction() {}
    void Generate(Stream& out) const override;
};

