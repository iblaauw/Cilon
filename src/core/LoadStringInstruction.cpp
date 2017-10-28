#include "LoadStringInstruction.h"

LoadStringInstruction::LoadStringInstruction(std::string value)
    : value(value)
{}

void LoadStringInstruction::Generate(std::ostream& out) const
{
    out << "    ldstr " << '"' << value << '"' << std::endl;
}

