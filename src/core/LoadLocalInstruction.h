#pragma once

#include <memory>

#include "Instruction.h"
#include "Name.h"

class LoadLocalInstruction : public Instruction
{
public:
    LoadLocalInstruction(int index);
    LoadLocalInstruction(Identifier paramName);

    void Generate(Stream& out) const override;

private:
    int index;
    std::unique_ptr<Identifier> name;
    bool isByName;
};

