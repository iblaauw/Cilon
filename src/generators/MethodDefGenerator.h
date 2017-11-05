#pragma once

#include "Generator.h"

class Method;
class MethodSignature;

class MethodDefGenerator : public Generator
{
public:
    MethodDefGenerator(const Method* method);
    void Generate(Stream& out) const override;

private:
    void GenerateParams(Stream& out, const MethodSignature& signature) const;
    void GenerateMethodBody(Stream& out) const;

    const Method* method;
};

class MethodDefParamsGenerator : public Generator
{
public:
    MethodDefParamsGenerator(const Method* method);
    void Generate(Stream& out) const override;

private:
    const Method* method;
};


