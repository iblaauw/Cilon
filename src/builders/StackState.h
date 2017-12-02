#pragma once

#include "ILType.h"


class StackState
{
public:
    StackState();
    StackState(const StackState& other) = default;
    StackState(StackState&& other) = default;

    void Push(ILType* type);
    ILType* Pop();

    bool MatchesTop(const std::vector<ILType*>& typesToMatch) const;
    bool Matches(const StackState& other) const;

    void Transition(const std::vector<ILType*>& typesToMatch, ILType* result);

private:
    std::vector<ILType*> types;
};

class TypeMismatchException : std::runtime_error
{
public:
    TypeMismatchException(std::string message) : std::runtime_error(message) {}
};


