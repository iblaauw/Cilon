#include "ReturnInstruction.h"

void ReturnInstruction::Generate(Stream& out) const
{
    out << "ret" << std::endl;
}

