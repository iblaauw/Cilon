#pragma once

#include "Generator.h"

class Module;

class ModuleGenerator : public Generator
{
public:
    ModuleGenerator(const Module* module);
    void Generate(Stream& out) const override;
private:
    const Module* module;
};


