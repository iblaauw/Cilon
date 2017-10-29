#include "ClassGenerator.h"

#include "ILType.h"
#include "Exceptions.h"
#include "TypeGenerator.h"
#include "MethodDefGenerator.h"

ClassGenerator::ClassGenerator(const ILType* type)
    : type(type)
{
    if (type == nullptr)
        throw NullArgumentException("'type' cannot be null");

    if (type->IsExternal())
        throw InvalidOperationException("Cannot generate a definition for an external class");
}

void ClassGenerator::Generate(Stream& out) const
{
    out << ".class private auto ansi " << TypeSpecGenerator(type) << std::endl;

    out << "{" << std::endl;
    out.IncrementIndent();

    for (const auto& keyval : type->AllMethods())
    {
        const Method* method = keyval.second.get();

        out << MethodDefGenerator(method) << std::endl;
    }

    out.DecrementIndent();
    out << "}" << std::endl;
}

