#pragma once

#include "Name.h"

class ILType
{
public:
    ILType(Name name, Module* owningModule);
    ILType(Name name, Assembly* owningAssembly);

    bool IsExternal() const;
    bool IsBuiltin() const;
    bool IsReferenceType() const { return true; } // TODO: implement

    Method* GetOrCreateMethod(Name methodName, MethodSignature signature);

private:
    Name name;
    UniqueDict<std::string, Method> methods;

    Assembly* owningAssembly;
    Module* owningModule;
    //UniqueDict<std::string, Field> field; // Uncomment once fields are implemented
    //UniqueDict<std::string, Property> properties; // Uncomment once properties are implemented
};

