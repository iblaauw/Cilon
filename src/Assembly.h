#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

#include "Name.h"
#include "ILType.h"

class Assembly
{
public:
    Assembly(Name name, bool isExternal);

    ILType* GetType(Name name);

    const Name& GetName() const;
    bool IsExternal() const;

    void Generate(std::ostream& out) const;
private:
    std::unordered_map<std::string, std::unique_ptr<ILType>> ownedTypes;
    Name name;
    bool isExternal;
};

