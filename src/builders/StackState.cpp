#include "StackState.h"

#include "Exceptions.h"

StackState::StackState()
    : types()
{}

void StackState::Push(ILType* type)
{
    types.push_back(type);
}

ILType* StackState::Pop()
{
    if (types.size() == 0)
        return nullptr;

    ILType* top = types.front();
    types.pop_back();
    return top;
}

bool StackState::MatchesTop(const std::vector<ILType*>& typesToMatch) const
{
    int size = typesToMatch.size();

    if (size == 0)
        return true;

    if (this->types.size() < size)
        return false;

    auto iter = types.cend() - size;
    for (int i = 0; i < size; i++)
    {
        if (*iter != typesToMatch[i])
            return false;

        iter++;
    }

    return true;
}

bool StackState::Matches(const StackState& other) const
{
    return types == other.types;
}

void StackState::Transition(const std::vector<ILType*>& typesToMatch, ILType* result)
{
    if (typesToMatch.size() > 0)
    {
        if (typesToMatch.size() > types.size())
            throw TypeMismatchException("Stack doesn't have enough values for the operation.");

        // Pop all the types to match off the stack
        for (const ILType* type : typesToMatch)
        {
            if (type == nullptr)
                throw NullArgumentException("'typesToMatch' contained a null value");

            ILType* topType = Pop();

            // Make sure the type we popped was valid
            if (type != topType)
            {
                std::stringstream ss;
                ss << "Expected type '";
                if (topType != nullptr)
                {
                    ss << topType->GetName();
                }
                else
                {
                    ss << "<none>";
                }
                ss << "' but recieved '" << type->GetName() << "' instead.";

                throw TypeMismatchException(ss.str());
            }
        }
    }

    if (result != nullptr)
    {
        Push(result);
    }
}

