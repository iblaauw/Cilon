#pragma once

#include "Name.h"
#include "UniqueDict.h"

class Module;
class Assembly;
class Method;
class MethodSignature;

class ILType
{
public:
    ILType(Name name, Module* owningModule);
    ILType(Name name, Assembly* owningAssembly);

    bool IsExternal() const;
    bool IsBuiltin() const;
    bool IsReferenceType() const { return true; } // TODO: implement

    Method* GetOrCreateMethod(Name methodName, const MethodSignature& signature);

private:
    Name name;
    UniqueDict<std::string, Method> methods;

    Assembly* owningAssembly;
    Module* owningModule;
    //UniqueDict<std::string, Field> field; // Uncomment once fields are implemented
    //UniqueDict<std::string, Property> properties; // Uncomment once properties are implemented
};

