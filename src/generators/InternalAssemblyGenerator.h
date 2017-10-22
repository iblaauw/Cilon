#pragma once

#include "Generator.h"

class InternalAssembly;

class InternalAssemblyGenerator : public Generator
{
public:
    InternalAssemblyGenerator(const InternalAssembly* assembly);
    void Generate(std::ostream& out) const override;
private:
    const InternalAssembly* assembly;
};

