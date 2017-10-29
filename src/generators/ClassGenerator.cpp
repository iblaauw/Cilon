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

void ClassGenerator::Generate(std::ostream& out) const
{
    out << ".class private auto ansi ";

    TypeSpecGenerator classNameGenerator(type);
    classNameGenerator.Generate(out);

    out << std::endl;

    out << "{" << std::endl;
    out << "    //TODO: class definitions" << std::endl;

    for (const auto& keyval : type->AllMethods())
    {
        const Method* method = keyval.second.get();
        MethodDefGenerator defGenerator { method };
        defGenerator.Generate(out);

        out << std::endl;
    }

    out << "}" << std::endl;
}

