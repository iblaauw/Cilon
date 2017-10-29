#include "ModuleGenerator.h"

#include "Module.h"
#include "MethodDefGenerator.h"
#include "ClassGenerator.h"

ModuleGenerator::ModuleGenerator(const Module* module)
    : module(module)
{}

void ModuleGenerator::Generate(Stream& out) const
{
    out << ".module ";
    if (module->IsExternal())
    {
        out << "extern ";
    }
    out << module->GetName() << std::endl;
    out << std::endl;

    if (!module->IsExternal())
    {
        for (const auto& keyval : module->AllMethods())
        {
            const Method* method = keyval.second.get();
            MethodDefGenerator defGenerator { method };
            defGenerator.Generate(out);
            out << std::endl;
        }

        for (const auto& keyval : module->AllTypes())
        {
            const ILType* type = keyval.second.get();

            ClassGenerator classGenerator { type };
            classGenerator.Generate(out);
        }
    }
}

