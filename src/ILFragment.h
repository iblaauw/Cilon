#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "TypeSet.h"

class ILFragment;

using ILFragmentPtr = std::unique_ptr<ILFragment>;

// This class is the root of all objects that produce IL
// It simply has a method to emit il code
class ILFragment
{
public:
    virtual void PreGenerate(std::ostream& out) const = 0;

    virtual void PostGenerate(std::ostream& out) const {}

    virtual const TypeSet& GetValidChildTypes() const = 0;

    void Generate(std::ostream& out) const;

    int size() const { return children.size(); }

    void Add(ILFragmentPtr child);
    void Insert(int index, ILFragmentPtr child);
    void Remove(int index);

    ILFragment* GetChild(int index);
    const ILFragment* GetChild(int index) const;
private:
    bool Validate(const ILFragmentPtr& child) const;

    std::vector<ILFragmentPtr> children;
};


