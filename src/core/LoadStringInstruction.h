#pragma once

#include "Instruction.h"

class LoadStringInstruction : public Instruction
{
public:
    LoadStringInstruction(std::string value);

    void Generate(std::ostream& out) const override;

    void SetValue(std::string value) { this->value = value; }
    std::string GetValue() const { return value; }

private:
    std::string value;
};

