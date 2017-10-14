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
    ILFile(std::string filename, Name assemblyName);

    Assembly* CreateReference(Name assemblyName);
    MethodDefinition* CreateMethod(Name methodName, std::shared_ptr<FunctionSignature> signature);

    void Generate(std::ostream& output) const;

private:
    std::unique_ptr<Assembly> currentAssembly;
    std::vector<std::unique_ptr<Assembly>> assemblyReferences;
    std::vector<std::unique_ptr<MethodDefinition>> methods;
    std::string name;
};
