#include "Method.h"

Method::Method(Name name, const MethodSignature& signature, Module* owningModule)
    : name(name), signature(signature), owningType(nullptr), owningModule(owningModule)
{
    // isStatic = true? not sure how to define top level methods
}

Method::Method(Name name, const MethodSignature& signature, ILType* owningType)
    : name(name), signature(signature), owningType(owningType), owningModule(nullptr)
{}

Method::Method(SpecialMethodType type, MethodSignature signature, ILType* owningType)
    : signature(signature), owningType(owningType), owningModule(nullptr)
{
    if (type == SpecialMethodType::Constructor)
    {
        isConstructor = true;
        name = ".ctor";
    }
    else if (type == SpecialMethodType::TypeInitializer)
    {
        isTypeInitializer = true;
        name = ".cctor";
    }
    else
    {
        throw InvalidArgumentException("Unrecognized SpecialMethodType value when creating a method");
    }
}

bool Method::IsExternal() const
{
    if (owningType != nullptr)
    {
        return owningType->IsExternal();
    }

    return owningModule->IsExternal();
}

void Method::AddInstruction(std::unique_ptr<Instruction> instr)
{
    if (IsExternal())
        throw InvalidOperatoion("Cannot set instructions for an externally defined method");

    instructions.emplace_back(std::move(instr));
}

