#pragma once

#include "Generator.h"

class Method;
class MethodSignature;

class MethodDefGenerator : public Generator
{
public:
    MethodDefGenerator(const Method* method);
    void Generate(std::ostream& out) const override;

private:
    void GenerateParams(std::ostream& out, const MethodSignature& signature) const;
    void GenerateMethodBody(std::ostream& out) const;

    const Method* method;
};


