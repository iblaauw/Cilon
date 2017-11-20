#include "DuplicateInstruction.h"

void DuplicateInstruction::Generate(Stream& out) const
{
    out << "dup";
}

