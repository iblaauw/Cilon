#include "Method.h"

#include "Exceptions.h"
#include "ILType.h"
#include "Module.h"

Method::Method(Name name, const MethodSignature& signature, Module* owningModule)
    : name(name), signature(signature), owningType(nullptr), owningModule(owningModule)
{
    // TODO: isStatic = true? not sure how to define top level methods
    parameterNames.resize(signature.NumParams());
}

Method::Method(Name name, const MethodSignature& signature, ILType* owningType)
    : name(name), signature(signature), owningType(owningType), owningModule(nullptr)
{
    parameterNames.resize(signature.NumParams());
}

Method::Method(SpecialMethodType type, const MethodSignature& signature, ILType* owningType)
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

    parameterNames.resize(signature.NumParams());
}

bool Method::IsExternal() const
{
    if (owningType != nullptr)
    {
        return owningType->IsExternal();
    }

    return owningModule->IsExternal();
}

bool Method::DoesParameterHaveName(int index) const
{
    ParameterNameIndexGuard(index);
    auto& paramName = parameterNames.at(index);
    return paramName != nullptr;
}

Identifier Method::GetParamName(int index) const
{
    ParameterNameIndexGuard(index);

    auto& paramName = parameterNames.at(index);
    if (paramName == nullptr)
        throw IndexOutOfRangeException("That parameter name is unset");

    return *paramName;
}

void Method::SetParamName(int index, const Identifier& name)
{
    ParameterNameIndexGuard(index);
    parameterNames[index] = std::make_unique<Identifier>(name);
}

void Method::UnsetParamName(int index)
{
    ParameterNameIndexGuard(index);
    parameterNames[index] = nullptr;
}

void Method::AddInstruction(std::unique_ptr<Instruction> instr)
{
    if (IsExternal())
        throw InvalidOperationException("Cannot set instructions for an externally defined method");

    instructions.emplace_back(std::move(instr));
}

void Method::ParameterNameIndexGuard(int index) const
{
    if (index < 0 || index >= parameterNames.size())
        throw IndexOutOfRangeException("Index out of range");

    if (IsExternal())
        throw InvalidOperationException("External methods don't have parameter names");
}

