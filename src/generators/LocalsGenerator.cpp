#include "LocalsGenerator.h"

#include "TypeGenerator.h"
#include "LocalsCollection.h"

#include "Exceptions.h"

LocalsGenerator::LocalsGenerator(const LocalsCollection& locals)
    : locals(locals)
{
}

void LocalsGenerator::Generate(Stream& stream) const
{
    if (locals.size() == 0)
        return;

    stream << ".locals init (";

    for (int i = 0; i < locals.size(); i++)
    {
        if (i != 0)
        {
            stream << ", ";
        }

        ILType* type = locals.GetType(i);
        stream << TypeGenerator { type };

        if (locals.HasName(i))
        {
            stream << " " << locals.GetName(i);
        }
    }

    stream << ")";
}

