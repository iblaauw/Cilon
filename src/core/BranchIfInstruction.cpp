#include "BranchIfInstruction.h"

#include "Exceptions.h"

BranchIfInstruction::BranchIfInstruction(const LabelInstruction* label)
    : BranchIfInstruction(label, true)
{}

BranchIfInstruction::BranchIfInstruction(const LabelInstruction* label, bool compareToTrue)
    : label(label), compareToTrue(compareToTrue)
{
    if (label == nullptr)
        throw NullArgumentException("'label' cannot be null");
}

void BranchIfInstruction::Generate(Stream& out) const
{
    if (compareToTrue)
    {
        out << "brtrue ";
    }
    else
    {
        out << "brfalse ";
    }

    out << label->GetName();
}
