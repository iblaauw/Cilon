#pragma once

#include "Instruction.h"

class LoadConstantInt : public Instruction
{
public:
    LoadConstantInt(int value);
    void Generate(Stream& out) const override;
private:
    int value;
};

