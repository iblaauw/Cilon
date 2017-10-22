#include "MethodSignature.h"

#include "Exceptions.h"

MethodSignature::MethodSignature(ILType* returnType)
{}

void MethodSignature::AddParameter(ILType* type, Identifier name)
{
    if (type == nullptr)
        throw NullArgumentException("Parameter type cannot be null");

    // TODO: if type == void, throw
    // TODO: validate that there are no duplicate named parameters

    MethodParameter param { type, name };
    parameters.push_back(param);
}

void MethodSignature::AddParameter(ILType* type)
{
    AddParameter(type, "");
}

MethodParameter& MethodSignature::GetParameter(int index)
{
    return parameters.at(index);
}

const MethodParameter& MethodSignature::GetParameter(int index) const
{
    return parameters.at(index);
}


