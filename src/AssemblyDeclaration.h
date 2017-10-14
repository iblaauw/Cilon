#pragma once

#include "ILFragment.h"
#include "Name.h"

class AssemblyDeclaration : public ILFragment
{
public:
    AssemblyDeclaration(Name assemblyName);

    void PreGenerate(std::ostream& out) const override;

    const TypeSet& GetValidChildTypes() const override
    {
        static TypeSet typeSet = CreateTypeSet<>();
        return typeSet;
    }

private:
    Name assemblyName;
};

