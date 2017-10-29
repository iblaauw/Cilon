#pragma once

class Stream;

class Generator
{
public:
    virtual void Generate(Stream& out) const  = 0;
};

#include "Stream.h"

