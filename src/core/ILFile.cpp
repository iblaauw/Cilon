#include "ILFile.h"

#include "Utils.h"

ILFile::ILFile(Name assemblyName, Name moduleName)
{
    currentAssembly = std::make_unique<InternalAssembly>(assemblyName, moduleName);
}

Assembly* GetOrCreateAssemblyReference(Name assemblyName)
{
    std::string key = assemblyName.GetString();
    return assemblyReference.GetOrCreateValue(key, assemblyName);
}

void ILFile::Generate(std::ostream& out) const
{
    ILFileGenerator generator { this };
    generator.Generate(out);
}

