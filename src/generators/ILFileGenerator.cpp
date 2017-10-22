#include "ILFileGenerator.h"

#include "Exceptions.h"
#include "ILFile.h"
#include "InternalAssemblyGenerator.h"
#include "ExternalAssemblyGenerator.h"

ILFileGenerator::ILFileGenerator(const ILFile* file)
    : file(file)
{
    if (file == nullptr)
        throw NullArgumentException("'file' cannot be null");
}

void ILFileGenerator::Generate(std::ostream& out) const
{
    const auto* currentAssembly = file->GetCurrentAssembly();
    const Name& name = currentAssembly->GetCurrentModule()->GetName();

    out << "//*****************************//" << std::endl;
    out << "// Begin file " << name << std::endl;
    out << "//*****************************//" << std::endl;

    for (const auto& keyval : *file)
    {
        const ExternalAssembly* assemblyRef = keyval.second.get();
        ExternalAssemblyGenerator generator { assemblyRef };
        generator.Generate(out);
    }

    InternalAssemblyGenerator internalGenerator { currentAssembly };
    internalGenerator.Generate(out);

    out << "//*****************************//" << std::endl;
    out << "// End file " << name << std::endl;
    out << "//*****************************//" << std::endl;
}

