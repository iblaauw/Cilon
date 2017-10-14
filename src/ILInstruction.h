#pragma once

#include <iostream>

class ILInstruction
{
public:
    virtual void Generate(std::ostream& out) const = 0;
};


