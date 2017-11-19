#include "BranchCompareInstruction.h"

#include "Exceptions.h"

BranchCompareInstruction::BranchCompareInstruction(const LabelInstruction* label, FullComparison comparison)
    : label(label), comparison(comparison)
{
    if (label == nullptr)
        throw NullArgumentException("'label' cannot be null");
}

BranchCompareInstruction::BranchCompareInstruction(const LabelInstruction* label, Comparison comparison)
    : label(label)
{
    if (label == nullptr)
        throw NullArgumentException("'label' cannot be null");

    // Comparison and FullComparison had better line up
    static_assert((int)Comparison::LessThan == (int)FullComparison::LessThan, "Comparison must align with FullComparison!");
    static_assert((int)Comparison::GreaterThan == (int)FullComparison::GreaterThan, "Comparison must align with FullComparison!");
    static_assert((int)Comparison::Equal == (int)FullComparison::Equal, "Comparison must align with FullComparison!");

    this->comparison = static_cast<FullComparison>(comparison);
}

void BranchCompareInstruction::Generate(Stream& out) const
{
    out << "b" << ComparisonToString();

    // TODO: there has GOT to be a cleaner way to do this
    if (comparison == FullComparison::NotEqual)
    {
        out << ".un";
    }

    out << " " << label->GetName();
}

const char* BranchCompareInstruction::ComparisonToString() const
{
    switch (comparison)
    {
    case FullComparison::LessThan:
        return "lt";
    case FullComparison::GreaterThan:
        return "gt";
    case FullComparison::Equal:
        return "eq";
    case FullComparison::GreaterOrEqual:
        return "ge";
    case FullComparison::LessOrEqual:
        return "le";
    case FullComparison::NotEqual:
        return "ne";
    default:
        throw InvalidOperationException("Unrecognized comparison type!");
    }
}

