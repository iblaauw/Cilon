#include "RawInstruction.h"

RawInstruction::RawInstruction(const std::string& str)
    : value(str)
{}

void RawInstruction::Generate(Stream& stream) const
{
    stream << value;
}
