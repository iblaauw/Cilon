#include "InternalAssemblyGenerator.h"

ExternalAssemblyGenerator::ExternalAssemblyGenerator(ExternalAssembly* assembly)
    : assembly(assembly)
{
    if (assembly == nullptr)
        throw NullArgmentException("'assembly' cannot be null");
}

void ExternalAssemblyGenerator::Generate(std::ostream& out) const
{
    out << ".assembly extern " << assembly->GetName() << " {}" << std::endl;
}

