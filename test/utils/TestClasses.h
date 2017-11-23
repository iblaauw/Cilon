#pragma once

#include <sstream>

#include "Stream.h"
#include "ILFile.h"

class StreamTest
{
public:
    StreamTest();
    void ResetStream();

protected:
    std::stringstream ss;
    Stream stream;
};

class ILFileTest : public StreamTest
{
public:
    ILFileTest();
protected:
    ILFile file;
    InternalAssembly* currentAssembly;
    Module* currentModule;
};

class MethodTest : public ILFileTest
{
public:
    MethodTest();
protected:
    Method* method;
};

