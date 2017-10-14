#include "MethodReference.h"

#include "ILType.h"

MethodReference::MethodReference(Name name,
    std::shared_ptr<FunctionSignature> signature,
    ILType* owningType)
    : name(name), signature(signature), owningType(owningType), isStatic(false)
{}

void MethodReference::GenerateCallHeader(std::ostream& out) const
{
    out << signature->GetReturnType() << ' ';

    if (owningType != nullptr)
    {
        out << owningType << "::";
    }

    out << name;

    signature->GenerateParamList(out);
}
