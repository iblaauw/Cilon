#include "FunctionSignature.h"

#include "ILType.h"

const ILType* FunctionSignature::GetReturnType() const
{
    return returnType;
}

const std::vector<const ILType*>& FunctionSignature::GetParameterTypes() const
{
    return parameterTypes;
}

void FunctionSignature::Generate(std::ostream& out) const
{
    out << "func-sig ";
    returnType->Generate(out);
    out << ' ';
    GenerateParamList(out);
}

void FunctionSignature::GenerateParamList(std::ostream& out) const
{
    out << "(";

    bool first = true;
    for (auto* param : parameterTypes)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            out << ", ";
        }
        param->Generate(out);
    }

    out << ")";
}
