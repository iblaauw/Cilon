#pragma once

#include "ILType.h"
#include "Method.h"

class Assembly;
class MethodSignature;

class Module
{
public:
    Module(Name name, Assembly* owner, bool isExternal);

    const Name& GetName() const { return name; }

    Assembly* GetAssembly() { return owningAssembly; }
    bool IsExternal() const { return isExternal; }

    ILType* GetOrCreateType(Name typeName);
    Method* GetOrCreateMethod(Name methodName, const MethodSignature& signature);

private:
    Name name;
    Assembly* owningAssembly;
    bool isExternal;
    UniqueDict<std::string, ILType> types;
    UniqueDict<std::string, Method> methods;
    // Commented out until fields are implemented
    // Can fields be exported?
    //UniqueDict<std::string, Field> field;
};


