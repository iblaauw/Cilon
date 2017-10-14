#pragma once

#include <vector>
#include <iostream>

class ILType;

class FunctionSignature
{
public:
    template <class... Params>
    FunctionSignature(const ILType* returnType, Params... paramTypes)
        : returnType(returnType),
        parameterTypes({ paramTypes... })
    {
    }

    const ILType* GetReturnType() const;
    const std::vector<const ILType*>& GetParameterTypes() const;

    // Not intended for actual use, just for debugging
    void Generate(std::ostream& out) const;

    void GenerateParamList(std::ostream& out) const;

private:
    const ILType* returnType;
    std::vector<const ILType*> parameterTypes;
};


