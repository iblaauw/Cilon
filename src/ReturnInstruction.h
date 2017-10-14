#pragma once

#include "ILInstruction.h"

class ReturnInstruction : public ILInstruction
{
public:
    ReturnInstruction() {}
    void Generate(std::ostream& out) const override;
};

