#pragma once

#include "Generator.h"

class Method;

class MethodDefGenerator : public Generator
{
public:
    MethodDefGenerator(const Method* method);
    void Generate(std::ostream& out) const override;

private:
    const Method* method;
};


