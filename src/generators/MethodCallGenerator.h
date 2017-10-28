#pragma once

#include "Generator.h"

class Method;
class MethodSignature;

class MethodCallGenerator : public Generator
{
public:
    MethodCallGenerator(const Method* method);
    void Generate(std::ostream& out) const override;

private:
    void GenerateParams(std::ostream& out, const MethodSignature& signature) const;

    const Method* method;
};
