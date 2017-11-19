#include "LabelInstruction.h"

LabelInstruction::LabelInstruction(const Identifier& name)
    : name(name)
{}

void LabelInstruction::Generate(Stream& out) const
{
    out << name << ":";
}

