#include "ILFile.h"

#include "Utils.h"
#include "ILFileGenerator.h"

ILFile::ILFile(Name moduleName, Name assemblyName)
{
    currentAssembly = std::make_unique<InternalAssembly>(assemblyName, moduleName);
}

ExternalAssembly* ILFile::GetOrCreateAssemblyReference(Name assemblyName)
{
    std::string key = assemblyName.GetString();
    return assemblyReferences.GetOrCreateValue(key, assemblyName);
}

void ILFile::Generate(std::ostream& out) const
{
    ILFileGenerator generator { this };
    generator.Generate(out);
}

