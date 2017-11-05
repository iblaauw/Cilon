#include "LoadConstantInt.h"

LoadConstantInt::LoadConstantInt(int value)
    : value(value)
{}

void LoadConstantInt::Generate(Stream& out) const
{
    out << "ldc.i4";

    // -1 builtin shortform
    if (value == -1)
    {
        out << ".m1";
        return;
    }

    // Other builtin shortforms
    if (value <= 8 && value >= 0)
    {
        out << "." << value;
        return;
    }

    // Normal shortform
    if (value <= 127 && value >= -128)
    {
        out << ".s " << value;
        return;
    }

    // Longform
    out << " " << value;
}

