#pragma once

#include "Instruction.h"
#include "RawInstruction.h"

class AndInstruction : public RawInstruction
{
public:
    AndInstruction() : RawInstruction("and") {}
};

class OrInstruction : public RawInstruction
{
public:
    OrInstruction() : RawInstruction("or") {}
};

class XOrInstruction : public RawInstruction
{
public:
    XOrInstruction() : RawInstruction("xor") {}
};

class ShiftLeftInstruction : public RawInstruction
{
public:
    ShiftLeftInstruction() : RawInstruction("shl") {}
};

class ShiftRightInstruction : public Instruction
{
public:
    void Generate(Stream& stream) const override;

    bool GetIsUnsigned() const { return isUnsigned; }
    void SetIsUnsigned(bool value) { isUnsigned = value; }

private:
    bool isUnsigned = false;
};

