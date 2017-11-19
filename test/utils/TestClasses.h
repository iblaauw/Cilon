#pragma once

#include <sstream>

#include "Stream.h"

class StreamTest
{
public:
    StreamTest();
    void ResetStream();

protected:
    std::stringstream ss;
    Stream stream;
};

