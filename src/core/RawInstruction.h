#pragma once

#include <string>

#include "Instruction.h"

class RawInstruction : public Instruction
{
public:
    RawInstruction(const std::string& str);

    void Generate(Stream& stream) const override;

protected:
    std::string value;
};
