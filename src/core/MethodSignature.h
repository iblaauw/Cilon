#pragma once

#include "Name.h"

class ILType;

class MethodParameter
{
public:
    MethodParameter(ILType* type, Identifier name)
        : type(type), name(name)
    {}

    ILType* type;
    Identifier name;
};

class MethodSignature
{
public:
    MethodSignature(ILType* returnType);

    const ILType* GetReturnType() const { return returnType; }

    int NumParams() const { return parameters.size(); }

    void AddParameter(ILType* type, Identifier name);
    void AddParameter(ILType* type);

    MethodParameter& GetParameter(int index);
    const MethodParameter& GetParameter(int index) const;

private:
    ILType* returnType;
    std::vector<MethodParameter> parameters;
};

