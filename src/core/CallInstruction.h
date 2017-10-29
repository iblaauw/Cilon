#pragma once

#include "Instruction.h"

class Method;

class CallInstruction : public Instruction
{
public:
    CallInstruction(Method* method);

    void Generate(Stream& out) const override;

private:
    Method* method;
};



