#include "TypeGenerator.h"

#include "Exceptions.h"
#include "ILType.h"
#include "Module.h"
#include "Assembly.h"

TypeReferenceGenerator::TypeReferenceGenerator(const ILType* type)
    : type(type)
{
    if (type == nullptr)
        throw NullArgumentException("'type' cannot be null");
}

void TypeReferenceGenerator::Generate(std::ostream& out) const
{
    if (!type->IsBuiltin() && type->IsExternal())
    {
        out << '[';
        Module* module = type->GetOwningModule();
        if (module != nullptr)
        {
            out << ".module " << module->GetName();
        }
        else
        {
            out << type->GetOwningAssembly()->GetName();
        }
        out << ']';
    }

    out << type->GetName();
}

TypeGenerator::TypeGenerator(const ILType* type)
    : type(type)
{
    if (type == nullptr)
        throw NullArgumentException("'type' cannot be null");
}

void TypeGenerator::Generate(std::ostream& out) const
{
    if (!type->IsBuiltin())
    {
        if (type->IsReferenceType())
        {
            out << "class ";
        }
        else
        {
            out << "valuetype ";
        }
        // TODO: implement more complicated types
    }

    TypeReferenceGenerator typeref { type };
    typeref.Generate(out);
}

/*static*/ bool TypeGenerator::RequiresFullType(const ILType* type)
{
    // TODO: array types and pointer types require the full type
    return false;
}

TypeSpecGenerator::TypeSpecGenerator(const ILType* type)
    : type(type)
{
    if (type == nullptr)
        throw NullArgumentException("'type' cannot be null");
}

void TypeSpecGenerator::Generate(std::ostream& out) const
{
    if (TypeGenerator::RequiresFullType(type))
    {
        TypeGenerator generator { type };
        generator.Generate(out);
    }
    else
    {
        TypeReferenceGenerator generator { type };
        generator.Generate(out);
    }
}


