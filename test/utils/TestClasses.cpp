#include "TestClasses.h"

StreamTest::StreamTest()
    : ss(), stream(ss)
{}

void StreamTest::ResetStream()
{
    ss.str(std::string());
}

