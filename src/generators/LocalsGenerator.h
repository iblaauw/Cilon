#pragma once

#include "Generator.h"

class LocalsCollection;

class LocalsGenerator : public Generator
{
public:
    LocalsGenerator(const LocalsCollection& locals);
    void Generate(Stream& stream) const;

private:
    const LocalsCollection& locals;
};

