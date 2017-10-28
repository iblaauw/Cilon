#include "MethodCallGenerator.h"

#include "Exceptions.h"
#include "Method.h"
#include "TypeGenerator.h"

MethodCallGenerator::MethodCallGenerator(const Method* method)
    : method(method)
{
}

void MethodCallGenerator::Generate(std::ostream& out) const
{
    const auto& signature = method->GetSignature();

    TypeSpecGenerator returnTypeGenerator { signature.GetReturnType() };
    returnTypeGenerator.Generate(out);

    out << " ";

    ILType* owningType = method->GetOwningType();
    if (method->GetOwningType() != nullptr)
    {
        TypeSpecGenerator owningTypeGenerator { owningType };
        owningTypeGenerator.Generate(out);
        out << "::";
    }

    out << method->GetName();

    GenerateParams(out, signature);
}

void MethodCallGenerator::GenerateParams(std::ostream& out, const MethodSignature& signature) const
{
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

        TypeSpecGenerator paramGen { paramType };
        paramGen.Generate(out);
    }
    out << ")";
}
