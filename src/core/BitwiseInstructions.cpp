#include "BitwiseInstructions.h"

void ShiftRightInstruction::Generate(Stream& stream) const
{
    stream << "shr";
    if (isUnsigned)
    {
        stream << ".un";
    }
}

