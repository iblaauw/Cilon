#include "LoadStringInstruction.h"

LoadStringInstruction::LoadStringInstruction(std::string value)
    : value(value)
{}

void LoadStringInstruction::Generate(Stream& out) const
{
    out << "ldstr " << '"' << value << '"' << std::endl;
}

