#pragma once

#include "Instruction.h"

class AddInstruction : public Instruction
{
public:
    void Generate(Stream& stream) const override
    {
        stream << "add";
    }
};

class SubtractInstruction : public Instruction
{
public:
    void Generate(Stream& stream) const override
    {
        stream << "sub";
    }
};

class MultiplyInstruction : public Instruction
{
public:
    void Generate(Stream& stream) const override
    {
        stream << "mul";
    }
};

class DivideInstruction : public Instruction
{
public:
    void Generate(Stream& stream) const override
    {
        stream << "div";
    }
};

class NegateInstruction : public Instruction
{
public:
    void Generate(Stream& stream) const override
    {
        stream << "neg";
    }
};
