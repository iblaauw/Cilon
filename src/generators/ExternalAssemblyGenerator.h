#pragma once

#include "Generator.h"

class ExternalAssembly;

class ExternalAssemblyGenerator : public Generator
{
public:
    ExternalAssemblyGenerator(const ExternalAssembly* assembly);
    void Generate(std::ostream& out) const override;
private:
    const ExternalAssembly* assembly;
};

