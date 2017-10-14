#include "AssemblyReference.h"

AssemblyReference::AssemblyReference(Name assemblyName)
    : assemblyName(assemblyName),
    aliasName()
{}

void AssemblyReference::PreGenerate(std::ostream& out) const
{
    out << ".assembly extern " << assemblyName;

    if (!aliasName.empty())
    {
        out << " as " << aliasName;
    }

    out << " {}" << std::endl;
}

