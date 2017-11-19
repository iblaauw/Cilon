#pragma once

#include "Instruction.h"
#include "Name.h"

class LabelInstruction : public Instruction
{
public:
    LabelInstruction(const Identifier& name);

    void Generate(Stream& out) const override;

    inline const Identifier& GetName() const { return name; }

private:
    Identifier name;
};

