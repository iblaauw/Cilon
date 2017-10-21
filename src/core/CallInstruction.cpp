#include "CallInstruction.h"

CallInstruction::CallInstruction(Method* method)
    : method(method)
{
    if (method == nullptr)
        throw NullArgumentException("Method cannot be null");
}

void CallInstruction::Generate(std::ostream& out) const
{
    out << "call ";
    //method->GenerateCallHeader(out); //TODO: implement
    out << std::endl;
}


