#include "ILFileGenerator.h"

ILFileGenerator::ILFileGenerator(ILFile* file)
    : file(file)
{
    if (file == nullptr)
        throw NullArgumentException("'file' cannot be null");
}

void ILFileGenerator::Generator(std::ostream& out) const
{
    out << "//*****************************//" << std::endl;
    out << "// Begin file " << name << std::endl;
    out << "//*****************************//" << std::endl;

    for (const auto& keyval : *file)
    {
        const ExternalAssembly* assemblyRef = keyval.second;
        ExternalAssemblyGenerator generator { assemblyRef };
        ref.Generator(out);
    }

    const auto* currentAssembly = file->GetCurrentAssembly();
    InternalAssemblyGenerator internalGenerator { currentAssembly };
    internalGenerator.Generate(out);

    out << "//*****************************//" << std::endl;
    out << "// End file " << name << std::endl;
    out << "//*****************************//" << std::endl;
}

