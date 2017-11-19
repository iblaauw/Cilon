#include "BranchInstruction.h"

#include "Exceptions.h"

BranchInstruction::BranchInstruction(const LabelInstruction* label)
    : label(label)
{
    if (label == nullptr)
        throw NullArgumentException("'label' cannot be null");
}

void BranchInstruction::Generate(Stream& out) const
{
    out << "br " << label->GetName();
}

