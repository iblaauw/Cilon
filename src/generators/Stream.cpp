#include "Stream.h"

Stream::Stream(std::ostream& output)
    : output(output)
{}

void Stream::PrintIndent()
{
    for (int i = 0; i < indentLevel; i++)
    {
        output << "    ";
    }
}

