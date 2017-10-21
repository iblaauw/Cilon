#pragma once

#include "Instruction.h"

class ReturnInstruction : public Instruction
{
public:
    ReturnInstruction() {}
    void Generate(std::ostream& out) const override;
};

