#include "PopInstruction.h"

void PopInstruction::Generate(Stream& out) const
{
    out << "pop";
}

