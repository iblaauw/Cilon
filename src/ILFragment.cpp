#include "ILFragment.h"

#include <stdexcept>

#include "Utils.h"
#include "Assert.h"


void ILFragment::Generate(std::ostream& out) const
{
    PreGenerate(out);
    for (const ILFragmentPtr& child : children)
    {
        child->Generate(out);
    }
    PostGenerate(out);
}

void ILFragment::Add(ILFragmentPtr child)
{
    Validate(child);
    children.emplace_back(std::move(child));
}

void ILFragment::Insert(int index, ILFragmentPtr child)
{
    Assert(index <= children.size(), "Index out of range");
    Validate(child);

    auto iter = children.begin() + index;
    children.emplace(iter, std::move(child));
}

void ILFragment::Remove(int index)
{
    Assert(index <= children.size(), "Index out of range");
    auto iter = children.begin() + index;
    children.erase(iter);
}

bool ILFragment::Validate(const ILFragmentPtr& child) const
{
    const auto& typeSet = GetValidChildTypes();
    std::type_index childType = typeid(*child);
    bool isValid = typeSet.count(childType) > 0;
    if (!isValid)
        throw std::logic_error(Format("Invalid child type: ", childType.name()));
}

ILFragment* ILFragment::GetChild(int index)
{
    return children.at(index).get();
}

const ILFragment* ILFragment::GetChild(int index) const
{
    return children.at(index).get();
}



