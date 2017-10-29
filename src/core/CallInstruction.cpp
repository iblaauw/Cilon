#include "CallInstruction.h"

#include "Exceptions.h"
#include "MethodCallGenerator.h"

CallInstruction::CallInstruction(Method* method)
    : method(method)
{
    if (method == nullptr)
        throw NullArgumentException("Method cannot be null");
}

void CallInstruction::Generate(Stream& out) const
{
    out << "call ";
    MethodCallGenerator callGenerator { method };
    callGenerator.Generate(out);
    out << std::endl;
}


