#pragma once

#include <memory>
#include <vector>

#include "MethodReference.h"
#include "ILInstruction.h"

class MethodDefinition : public MethodReference
{
public:
    MethodDefinition(Name name, std::shared_ptr<FunctionSignature> signature);

    void SetStackSize(int value) { stackSize = value; }
    int GetStackSize() const { return stackSize; }

    void SetIsEntryPoint(bool value) { isEntryPoint = value; }
    bool GetIsEntryPoint() const { return isEntryPoint; }

    void AddInstruction(std::unique_ptr<ILInstruction> instr);

    void Generate(std::ostream& out) const;
private:
    std::vector<std::unique_ptr<ILInstruction>> instructions;
    int stackSize;
    bool isEntryPoint;
};

/*
class MethodDefinition : public ILFragment
{
public:
    MethodDefinition(std::string name);

    void PreGenerate(std::ostream& out) const override;
    void PostGenerate(std::ostream& out) const override;

    const TypeSet& GetValidChildTypes() const override;

    void SetIsEntryPoint(bool value) { isEntryPoint = value; }
    bool GetIsEntryPoint() const { return isEntryPoint; }

    void SetStackSize(int value) { stackSize = value; }
    int GetStackSize() const { return stackSize; }

private:
    std::string name;
    int stackSize;
    bool isEntryPoint = false;
};
*/

