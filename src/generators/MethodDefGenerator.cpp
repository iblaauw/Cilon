#include "MethodDefGenerator.h"

#include "Method.h"
#include "TypeGenerator.h"

MethodDefGenerator::MethodDefGenerator(const Method* method)
    : method(method)
{}

void MethodDefGenerator::Generate(std::ostream& out) const
{
    out << ".method ";
    if (method->IsStatic())
    {
        out << "static ";
    }
    out << "public ";

    const auto& signature = method->GetSignature();
    const ILType* returnType = method->GetSignature().GetReturnType();
    TypeGenerator returnTypeGen { returnType };
    returnTypeGen.Generate(out);

    out << " " << method->GetName();

    GenerateParams(out, signature);

    out << " cil managed" << std::endl;

    out << "{" << std::endl;

    GenerateMethodBody(out);

    out << "}" << std::endl;
}

void MethodDefGenerator::GenerateParams(std::ostream& out, const MethodSignature& signature) const
{
    // Generate parameters
    out << "(";

    bool first = true;
    for (ILType* paramType : signature.AllParameters())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            out << ", ";
        }

        TypeGenerator paramGen { paramType };
        paramGen.Generate(out);
    }

    // TODO: named parameters

    out << ")";
}

void MethodDefGenerator::GenerateMethodBody(std::ostream& out) const
{
    if (method->IsEntryPoint())
    {
        out << "    .entrypoint" << std::endl;
    }

    int stackSize = method->GetStackSize();
    if (stackSize > 0)
    {
        out << "    .maxstack " << stackSize << std::endl;
    }

    for (auto& instr : method->AllInstructions())
    {
        instr->Generate(out);
    }
}


