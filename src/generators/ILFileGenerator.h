#pragma once

#include "Generator.h"

class ILFile;

class ILFileGenerator : public Generator
{
public:
    ILFileGenerator(const ILFile* file);
    void Generate(std::ostream& out) const override;
private:
    const ILFile* file;
};

