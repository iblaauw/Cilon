#pragma once

#include "Name.h"

#include <memory>

class ILType;

class LocalsCollection
{
public:
    void Add(ILType* type);
    void Add(ILType* type, Identifier name);

    int size() const;

    bool HasName(int index) const;
    Identifier GetName(int index) const;
    ILType* GetType(int index) const;

private:
    void IndexGuard(int index) const;

    std::vector<ILType*> types;
    std::vector<std::unique_ptr<Identifier>> names;
};


