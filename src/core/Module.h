#pragma once

#include "Range.h"
#include "ILType.h"
#include "Method.h"

class Assembly;
class MethodSignature;

class Module
{
public:
    using type_iter = typename UniqueDict<std::string, ILType>::const_iterator;
    using method_iter = typename UniqueDict<std::string, Method>::const_iterator;

    Module(Name name, Assembly* owner, bool isExternal);

    const Name& GetName() const { return name; }

    Assembly* GetAssembly() { return owningAssembly; }
    bool IsExternal() const { return isExternal; }

    ILType* GetOrCreateType(Name typeName);
    Method* GetOrCreateMethod(Name methodName, const MethodSignature& signature);

    Range<type_iter> AllTypes() const
    {
        return { types.begin(), types.end() };
    }

    Range<method_iter> AllMethods() const
    {
        return { methods.begin(), methods.end() };
    }

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


