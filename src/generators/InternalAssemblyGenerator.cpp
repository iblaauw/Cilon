#include "InternalAssemblyGenerator.h"

InternalAssemblyGenerator::InternalAssemblyGenerator(InternalAssembly* assembly)
    : assembly(assembly)
{
    if (assembly == nullptr)
        throw NullArgmentException("'assembly' cannot be null");
}

void InternalAssemblyGenerator::Generate(std::ostream& out) const
{
    out << ".assembly " << assembly->GetName() << "{}" << std::endl;
    out << "//TODO: generate methods / classes" << std::endl;
}

