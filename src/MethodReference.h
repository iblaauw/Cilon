#pragma once

#include <memory>

#include "Name.h"
#include "FunctionSignature.h"

class ILType;

class MethodReference
{
public:
    MethodReference(Name name, std::shared_ptr<FunctionSignature> signature, ILType* owningType);

    void SetIsStatic(bool value) { isStatic = value; }
    bool GetIsStatic() const { return isStatic; }

    void GenerateCallHeader(std::ostream& out) const;

protected:
    Name name;
    std::shared_ptr<FunctionSignature> signature;
    ILType* owningType;
    bool isStatic;
};
