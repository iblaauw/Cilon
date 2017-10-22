#pragma once

#include <iostream>

class Generator
{
public:
    virtual void Generate(std::ostream& out) const  = 0;
};

