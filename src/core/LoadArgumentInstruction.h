#pragma once

#include <memory>

#include "Instruction.h"
#include "Name.h"

class LoadArgumentInstruction : public Instruction
{
public:
    LoadArgumentInstruction(int index);
    LoadArgumentInstruction(Identifier paramName);

    void Generate(Stream& out) const override;

private:
    int index;
    std::unique_ptr<Identifier> name;
    bool isByName;
};
