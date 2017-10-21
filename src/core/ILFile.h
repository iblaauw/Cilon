#pragma once

#include <iostream>
#include <memory>

#include "Name.h"
#include "Assembly.h"
#include "MethodDefinition.h"
#include "FunctionSignature.h"

class ILFile
{
public:
    ILFile(Name assemblyName, Name moduleName);

    InternalAssembly* GetCurrentAssembly() const
    {
        return currentAssembly.get();
    }

    ExternalAssembly* GetOrCreateAssemblyReference(Name assemblyName);

    auto begin() const -> decltype(assemblyReferences.begin())
    {
        return assemblyReferences.begin();
    }

    auto end() const -> decltype(assemblyReferences.end())
    {
        return assemblyReferences.end();
    }

    void Generate(std::ostream& output) const;

private:
    std::unique_ptr<InternalAssembly> currentAssembly;
    UniqueDict<std::string, ExternalAssembly> assemblyReferences;
};

