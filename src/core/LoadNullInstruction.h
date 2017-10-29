#pragma once

#include "Instruction.h"

class LoadNullInstruction : public Instruction
{
public:
    LoadNullInstruction() {};

    void Generate(Stream& out) const override;
};

