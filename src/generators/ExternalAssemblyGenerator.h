#pragma once

#include "Generator.h"

class ExternalAssemblyGenerator : public Generator
{
public:
    ExternalAssemblyGenerator(ExternalAssembly* assembly);
    void Generate(std::ostream& out) const override;
private:
    ExternalAssembly* assembly;
};

