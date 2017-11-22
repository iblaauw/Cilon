#include "LoadLocalInstruction.h"

#include "Utils.h"
#include "Exceptions.h"

LoadLocalInstruction::LoadLocalInstruction(int index)
    : index(index), name(nullptr), isByName(false)
{
    if (index < 0)
        throw InvalidArgumentException("'index' cannot be negative");
}

LoadLocalInstruction::LoadLocalInstruction(Identifier paramName)
    : index(-1), isByName(true)
{
    name = std::make_unique<Identifier>(paramName);
}

void LoadLocalInstruction::Generate(Stream& out) const
{
    out << "ldloc";
    if (isByName)
    {
        // Easy case, just output name and be done
        out << " " << *name;
        return;
    }

    if (index < 4)
    {
        out << "." << index;
    }
    else if (index < 256)
    {
        out << ".s " << index;
    }
    else
    {
        out << " " << index;
    }
}

