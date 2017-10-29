#pragma once

#include "Generator.h"

class Method;
class MethodSignature;

class MethodCallGenerator : public Generator
{
public:
    MethodCallGenerator(const Method* method);
    void Generate(Stream& out) const override;

private:
    void GenerateParams(Stream& out, const MethodSignature& signature) const;

    const Method* method;
};
