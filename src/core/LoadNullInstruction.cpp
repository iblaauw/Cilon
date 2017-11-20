#include "LoadNullInstruction.h"

void LoadNullInstruction::Generate(Stream& out) const
{
    out << "ldnull";
}


