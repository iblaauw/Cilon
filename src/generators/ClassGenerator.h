#pragma once

#include "Generator.h"

class ILType;

class ClassGenerator : public Generator
{
public:
    ClassGenerator(const ILType* tyoe);
    void Generate(Stream& out) const override;

private:
    const ILType* type;
};

