#pragma once

#include "Name.h"
#include "UniqueDict.h"
#include "Range.h"

class Module;
class Assembly;
class Method;
class MethodSignature;

class ILType
{
public:
    using method_iter = typename UniqueDict<std::string, Method>::const_iterator;

    ILType(Name name, Module* owningModule);
    ILType(Name name, Assembly* owningAssembly);

    bool IsExternal() const;
    bool IsBuiltin() const;
    bool IsReferenceType() const { return true; } // TODO: implement

    Method* GetOrCreateMethod(Name methodName, const MethodSignature& signature);

    // Common builtins
    static ILType* GetVoid();
    static ILType* GetString();
    static ILType* GetInt();
    static ILType* GetObject();

    const Name& GetName() const { return name; }
    Assembly* GetOwningAssembly() const { return owningAssembly; }
    Module* GetOwningModule() const { return owningModule; }

    Range<method_iter> AllMethods() const { return { methods.begin(), methods.end() }; }

private:
    Name name;
    UniqueDict<std::string, Method> methods;

    Assembly* owningAssembly;
    Module* owningModule;
    //UniqueDict<std::string, Field> field; // Uncomment once fields are implemented
    //UniqueDict<std::string, Property> properties; // Uncomment once properties are implemented
};

