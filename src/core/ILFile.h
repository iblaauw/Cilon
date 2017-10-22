#pragma once

#include <iostream>

#include "Name.h"
#include "UniqueDict.h"
#include "Assembly.h"

class ILFile
{
public:
    using const_iterator = typename UniqueDict<std::string, ExternalAssembly>::const_iterator;

    ILFile(Name moduleName, Name assemblyName);

    InternalAssembly* GetCurrentAssembly() const
    {
        return currentAssembly.get();
    }

    ExternalAssembly* GetOrCreateAssemblyReference(Name assemblyName);

    const_iterator begin() const
    {
        return assemblyReferences.begin();
    }

    const_iterator end() const
    {
        return assemblyReferences.end();
    }

    void Generate(std::ostream& output) const;

private:
    std::unique_ptr<InternalAssembly> currentAssembly;
    UniqueDict<std::string, ExternalAssembly> assemblyReferences;
};

