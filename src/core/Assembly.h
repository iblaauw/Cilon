#pragma once

#include "Name.h"
#include "ILType.h"

// Abstract base clase for assemblies
class Assembly
{
public:
    Assembly(Name assemblyName)
        : name(assemblyName)
    {}

    const Name& GetName() const { return name; }
    virtual bool IsExternal() const override = 0;

private:
    Name name;
};

class ExternalAssembly : public Assembly
{
public:
    ExternalAssembly(Name assemblyName);

    bool IsExternal() const override { return true; }

    ILType* GetOrCreateExportedType(Name name);

private:
    UniqueDict<std::string, ILType> ownedTypes;
};

class InternalAssembly : public Assembly
{
public:
    InternalAssembly(Name assemblyName, Name moduleName);

    bool IsExternal() const override { return false; }

    Module* GetCurrentModule() const { return currentModule.get(); }

    Module* GetOrCreateModuleReference(Name moduleName);

private:
    std::unique_ptr<Module> currentModule;
    UniqueDict<std::string, Module> externalModules;
};


