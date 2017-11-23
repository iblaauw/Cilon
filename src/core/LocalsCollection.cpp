#include "LocalsCollection.h"

#include "ILType.h"
#include "Exceptions.h"

void LocalsCollection::Add(ILType* type)
{
    if (type == ILType::GetVoid())
        throw InvalidArgumentException("Cannot add a local of type 'void'");

    types.push_back(type);
    names.push_back(nullptr);
}

void LocalsCollection::Add(ILType* type, Identifier name)
{
    if (type == ILType::GetVoid())
        throw InvalidArgumentException("Cannot add a local of type 'void'");

    types.push_back(type);
    names.push_back(std::make_unique<Identifier>(name));
}

int LocalsCollection::size() const
{
    return types.size();
}

bool LocalsCollection::HasName(int index) const
{
    IndexGuard(index);
    return names.at(index) != nullptr;
}

Identifier LocalsCollection::GetName(int index) const
{
    IndexGuard(index);

    auto& name = names.at(index);
    if (name == nullptr)
        throw InvalidOperationException("Local variable does not have a name");

    return *name;
}

ILType* LocalsCollection::GetType(int index) const
{
    IndexGuard(index);

    return types.at(index);
}

void LocalsCollection::IndexGuard(int index) const
{
    if (index < 0 || index >= types.size())
        throw IndexOutOfRangeException("Index out of Range");
}

