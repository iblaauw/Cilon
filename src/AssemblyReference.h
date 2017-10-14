#pragma once

#include "ILFragment.h"
#include "Name.h"

class AssemblyReference : public ILFragment
{
public:
    AssemblyReference(Name assemblyName);

    void PreGenerate(std::ostream& out) const override;

    const TypeSet& GetValidChildTypes() const override
    {
        static TypeSet typeSet = CreateTypeSet<>();
        return typeSet;
    }

    void SetAlias(const Name& name)
    {
        aliasName = name;
    }

private:
    Name assemblyName;
    Name aliasName;
};

