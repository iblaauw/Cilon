#include "ReturnInstruction.h"

void ReturnInstruction::Generate(std::ostream& out) const
{
    out << "ret" << std::endl;
}

