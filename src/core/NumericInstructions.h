#pragma once

#include "RawInstruction.h"

class AddInstruction : public RawInstruction
{
public:
    AddInstruction() : RawInstruction("add") {}
};

class SubtractInstruction : public RawInstruction
{
public:
    SubtractInstruction() : RawInstruction("sub") {}
};

class MultiplyInstruction : public RawInstruction
{
public:
    MultiplyInstruction() : RawInstruction("mul") {}
};

class DivideInstruction : public RawInstruction
{
public:
    DivideInstruction() : RawInstruction("div") {}
};

class NegateInstruction : public RawInstruction
{
public:
    NegateInstruction() : RawInstruction("neg") {}
};

