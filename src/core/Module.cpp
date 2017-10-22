#include "Module.h"

Module::Module(Name name, Assembly* owner, bool isExternal)
    : name(name), owningAssembly(owner), isExternal(isExternal)
{}

ILType* Module::GetOrCreateType(Name typeName)
{
    std::string key = typeName.GetString();
    return types.GetOrCreateValue(key, typeName, this);
}

Method* Module::GetOrCreateMethod(Name methodName, const MethodSignature& signature)
{
    std::string key = methodName.GetString();
    return methods.GetOrCreateValue(key, methodName, signature, this);
}

