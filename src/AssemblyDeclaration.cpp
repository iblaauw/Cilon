#include "AssemblyDeclaration.h"

AssemblyDeclaration::AssemblyDeclaration(Name assemblyName)
    : assemblyName(assemblyName)
{}

void AssemblyDeclaration::PreGenerate(std::ostream& out) const
{
    out << ".assembly " << assemblyName << " {}" << std::endl;
}

