#pragma once

#include "Generator.h"

class ILType;

// In syntax this is either TypeRef or TypeSpec
class TypeReferenceGenerator : public Generator
{
public:
    TypeReferenceGenerator(const ILType* type);
    void Generate(std::ostream& out) const override;
private:
    const ILType* type;
};

class TypeGenerator : public Generator
{
public:
    TypeGenerator(const ILType* type);
    void Generate(std::ostream& out) const override;
    static bool RequiresFullType(const ILType* type);
private:
    const ILType* type;
};

class TypeSpecGenerator : public Generator
{
public:
    TypeSpecGenerator(const ILType* type);
    void Generate(std::ostream& out) const override;
private:
    const ILType* type;
};


