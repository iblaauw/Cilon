#pragma once

// Used by CompareInstruction
// Note that the same semantics as FullComparison can be achieved by using negation
enum class Comparison
{
    LessThan,
    GreaterThan,
    Equal
};

// Used by BranchCompareInstruction
// IMPORTANT: the first values here must match the values in Comparison
enum class FullComparison
{
    LessThan,
    GreaterThan,
    Equal,
    GreaterOrEqual,
    LessOrEqual,
    NotEqual
};

