#include "InternalAssemblyGenerator.h"

#include "Exceptions.h"
#include "Assembly.h"
#include "ModuleGenerator.h"

InternalAssemblyGenerator::InternalAssemblyGenerator(const InternalAssembly* assembly)
    : assembly(assembly)
{
    if (assembly == nullptr)
        throw NullArgumentException("'assembly' cannot be null");
}

void InternalAssemblyGenerator::Generate(std::ostream& out) const
{
    out << ".assembly " << assembly->GetName() << "{}" << std::endl;
    out << std::endl;

    for (const auto& keyval : assembly->AllExternalModules())
    {
        const Module* externalModule = keyval.second.get();
        ModuleGenerator generator { externalModule };
        generator.Generate(out);
    }

    ModuleGenerator generator { assembly->GetCurrentModule() };
    generator.Generate(out);
}

