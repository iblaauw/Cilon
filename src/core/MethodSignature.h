#pragma once

#include "Name.h"
#include "Range.h"

class ILType;

class MethodSignature
{
public:
    MethodSignature(ILType* returnType);

    const ILType* GetReturnType() const { return returnType; }

    int NumParams() const { return parameters.size(); }

    void AddParameter(ILType* type);

    ILType* GetParameterType(int index) const;

private:
    ILType* returnType;
    std::vector<ILType*> parameters;

public:
    using const_iter = decltype(parameters.cbegin());
    Range<const_iter> AllParameters() const
    {
        return { parameters.begin(), parameters.end() };
    }
};

