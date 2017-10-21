#pragma once

#include "Generator.h"

class InternalAssemblyGenerator : public Generator
{
public:
    InternalAssemblyGenerator(InternalAssembly* assembly);
    void Generate(std::ostream& out) const override;
private:
    InternalAssembly* assembly;
};

