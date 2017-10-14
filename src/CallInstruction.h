#pragma once

#include "ILInstruction.h"
#include "MethodReference.h"

class CallInstruction : public ILInstruction
{
public:
    CallInstruction(MethodReference* method);

    void Generate(std::ostream& out) const override;

private:
    MethodReference* method;
};



