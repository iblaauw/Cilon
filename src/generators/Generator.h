#pragma once

#include "Stream.h"

class Generator
{
public:
    virtual void Generate(Stream& out) const  = 0;
};

