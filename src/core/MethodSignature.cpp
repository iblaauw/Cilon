#include "MethodSignature.h"

#include "Exceptions.h"

MethodSignature::MethodSignature(ILType* returnType)
    : returnType(returnType)
{}

void MethodSignature::AddParameter(ILType* type)
{
    if (type == nullptr)
        throw NullArgumentException("Parameter type cannot be null");

    // TODO: if type == void, throw

    parameters.push_back(type);
}

ILType* MethodSignature::GetParameterType(int index) const
{
    return parameters.at(index);
}

