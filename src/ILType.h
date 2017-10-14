#pragma once

#include <iostream>
#include <unordered_map>

#include "Name.h"
#include "MethodReference.h"

class Assembly;
class FunctionSignature;

class ILType
{
public:
    ILType(Name name, const Assembly* owningAssembly);

    static ILType* GetVoid();
    static ILType* GetString();
    static ILType* GetInt();

    MethodReference* GetMethod(Name name, std::shared_ptr<FunctionSignature> signature);

    void Generate(std::ostream& out) const;

    bool IsBuiltinType() const { return assembly == nullptr; }

private:
    std::unordered_map<std::string, std::unique_ptr<MethodReference>> ownedMethods;
    Name name;
    const Assembly* assembly;
};

std::ostream& operator<<(std::ostream& out, const ILType& type);
std::ostream& operator<<(std::ostream& out, const ILType* type);

