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

    out << " " << method->GetName() << " (";

    // Generate parameters
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

    out << ") cil managed" << std::endl;
    out << "{" << std::endl;
    out << "//TODO: Definition" << std::endl;
    out << "}" << std::endl;
}


