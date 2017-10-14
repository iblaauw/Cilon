#include "CallInstruction.h"

CallInstruction::CallInstruction(MethodReference* method)
    : method(method)
{}

void CallInstruction::Generate(std::ostream& out) const
{
    out << "call ";
    method->GenerateCallHeader(out);
    out << std::endl;
}


