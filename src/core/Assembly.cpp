#include "Assembly.h"

#include "Method.h"

ExternalAssembly::ExternalAssembly(Name assemblyName)
    : Assembly(assemblyName), ownedTypes()
{
}

ILType* ExternalAssembly::GetOrCreateExportedType(Name name)
{
    std::string key = name.GetString();
    return ownedTypes.GetOrCreateValue(key, name, this);
}

InternalAssembly::InternalAssembly(Name assemblyName, Name moduleName)
    : Assembly(assemblyName)
{
    currentModule = std::make_unique<Module>(moduleName, this, /*isExternal*/ false);
}

Module* InternalAssembly::GetOrCreateModuleReference(Name moduleName)
{
    std::string key = moduleName.GetString();
    return externalModules.GetOrCreateValue(key, moduleName, this, /*isExternal*/ true);
}


