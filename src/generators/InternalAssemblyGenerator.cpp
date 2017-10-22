#include "InternalAssemblyGenerator.h"

#include "Exceptions.h"
#include "Assembly.h"

InternalAssemblyGenerator::InternalAssemblyGenerator(const InternalAssembly* assembly)
    : assembly(assembly)
{
    if (assembly == nullptr)
        throw NullArgumentException("'assembly' cannot be null");
}

void InternalAssemblyGenerator::Generate(std::ostream& out) const
{
    out << ".assembly " << assembly->GetName() << "{}" << std::endl;
    out << "//TODO: generate methods / classes" << std::endl;
}

