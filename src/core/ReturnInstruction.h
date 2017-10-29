#pragma once

#include "Instruction.h"

class ReturnInstruction : public Instruction
{
public:
    ReturnInstruction() {}
    void Generate(Stream& out) const override;
};

