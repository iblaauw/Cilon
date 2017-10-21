#pragma once

#include "Instruction.h"

class CallInstruction : public Instruction
{
public:
    CallInstruction(Method* method);

    void Generate(std::ostream& out) const override;

private:
    Method* method;
};



