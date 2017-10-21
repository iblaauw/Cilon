#include "ILType.h"

ILType::ILType(Name name, Module* owningModule)
    : name(name), owningAssembly(nullptr), owningModule(owningModule)
{}

ILType::ILType(Name name, Assembly* owningAssembly);
    : name(name), owningAssembly(owningAssembly), owningModule(nullptr)


bool ILType::IsExternal() const
{
    if (owningAssembly != nullptr)
        return true;

    if (owningModule == nullptr)
        return true; // Both are null means builtin type

    return owningModule->IsExternal();
}

bool ILType::IsBuiltin() const
{
    return owningAssembly == nullptr && owningModule == nullptr;
}

Method* ILType::GetOrCreateMethod(Name methodName, MethodSignature signature)
{
    std::string key = methodName.GetString();
    return methods.GetOrCreateValue(key, methodName, signature, this);
}


