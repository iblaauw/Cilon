#include "ExternalAssemblyGenerator.h"

#include "Exceptions.h"
#include "Assembly.h"

ExternalAssemblyGenerator::ExternalAssemblyGenerator(const ExternalAssembly* assembly)
    : assembly(assembly)
{
    if (assembly == nullptr)
        throw NullArgumentException("'assembly' cannot be null");
}

void ExternalAssemblyGenerator::Generate(Stream& out) const
{
    out << ".assembly extern " << assembly->GetName() << " {}" << std::endl;
}

