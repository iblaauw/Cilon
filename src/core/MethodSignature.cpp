#include "MethodSignature.h"

MethodSignature::MethodSignature(ILType* returnType)
{}

void MethodSignature::AddParameter(ILType* type, Identifier name)
{
    if (type == nullptr)
        throw NullArgumentException("Parameter type cannot be null");

    // TODO: if type == void, throw
    // TODO: validate that there are no duplicate named parameters

    MethodParameter param;
    param.type = type;
    param.name = name;

    parameters.push_back(param);
}

MethodParameter& MethodSignature::GetParameter(int index)
{
    return parameters.at(index):
}

const MethodParameter& MethodSignature::GetParameter(int index) const
{
    return parameters.at(index):
}


