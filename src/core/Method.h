#pragma once

#include <memory>
#include <map>

#include "Name.h"
#include "Instruction.h"
#include "MethodSignature.h"

class Module;

class Method
{
public:
    enum class SpecialMethodType { Constructor, TypeInitializer };

    Method(Name name, const MethodSignature& signature, Module* owningModule);
    Method(Name name, const MethodSignature& signature, ILType* owningType);
    Method(SpecialMethodType type, const MethodSignature& signature, ILType* owningType);

    const Name& GetName() const { return name; }

    int GetStackSize() const { return stackSize; }
    void SetStackSize(int value) { stackSize = value; }

    bool IsExternal() const;
    bool IsConstructor() const { return isConstructor; }
    bool IsTypeInitializer() const { return isTypeInitializer; }

    bool IsStatic() const { return isStatic; }
    void SetIsStatic(bool value) { isStatic = value; }

    bool IsEntryPoint() const { return isEntryPoint; }
    void SetIsEntryPoint(bool value) { isEntryPoint = value; }

    ILType* GetOwningType() const { return owningType; }
    Module* GetOwningModule() const { return owningModule; }

    bool DoesParameterHaveName(int index) const;
    Identifier GetParamName(int index) const;
    void SetParamName(int index, const Identifier& name);
    void UnsetParamName(int index);

    const MethodSignature& GetSignature() const { return signature; }

    void AddInstruction(std::unique_ptr<Instruction> instr);

    using instr_iter = typename std::vector<std::unique_ptr<Instruction>>::const_iterator;

    Range<instr_iter> AllInstructions() const { return { instructions.begin(), instructions.end() }; }

private:
    void ParameterNameIndexGuard(int index) const;

    std::vector<std::unique_ptr<Instruction>> instructions;
    std::vector<std::unique_ptr<Identifier>> parameterNames; // These are pointers in order to allow them to be null (which means not set)

    Name name;
    MethodSignature signature;

    ILType* owningType;
    Module* owningModule;

    int stackSize = 0;

    bool isConstructor = false;
    bool isTypeInitializer = false;
    bool isStatic = false;
    bool isEntryPoint = false;
};

