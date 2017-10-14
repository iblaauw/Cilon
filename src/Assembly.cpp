#include "Assembly.h"

#include "Utils.h"


Assembly::Assembly(Name name, bool isExternal)
    : name(name), isExternal(isExternal)
{
}

ILType* Assembly::GetType(Name name)
{
    std::string key = name.GetString();

    auto iter = ownedTypes.find(key);
    if (iter != ownedTypes.end())
    {
        // Type has been created already
        return iter->second.get();
    }

    // Need to create the type
    std::unique_ptr<ILType> type = std::make_unique<ILType>(name, this);
    ILType* typeWeak = type.get();

    ownedTypes.emplace(key, std::move(type));

    return typeWeak;
}

const Name& Assembly::GetName() const
{
    return name;
}

bool Assembly::IsExternal() const
{
    return isExternal;
}

void Assembly::Generate(std::ostream& out) const
{
    out << ".assembly ";
    if (isExternal)
    {
        out << "extern ";
    }
    out << name << " {}" << std::endl;
}


