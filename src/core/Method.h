#pragma once

class Method
{
public:
    enum class SpecialMethodType { Constructor, TypeInitializer };

    Method(Name name, const MethodSignature& signature, Module* owningModule);
    Method(Name name, const MethodSignature& signature, ILType* owningType);
    Method(SpecialMethodType type, const MethodSignature& signature, ILType* owningType);

    bool IsExternal() const;
    bool IsConstructor() const { return isConstructor; }
    bool IsTypeInitializer() const { return isTypeInitializer; }

    bool IsStatic() const { return isStatic; }
    void SetStatic(bool value) { isStatic = value; }

    bool IsEntryPoint() const { return isEntryPoint; }
    void SetIsEntryPoint(bool value) { isEntryPoint = value; }

    ILType* GetOwningType() const { return owningType; }
    Module* GetOwningModule() const { return owningModule; }

    const MethodSignature& GetSignature() const { return signature; }

    void AddInstruction(std::unique_ptr<Instruction> instr);

private:
    std::vector<std::unique_ptr<Instruction>> instructions;

    Name name;
    MethodSignature signature;

    ILType* owningType;
    Module* owningModule;

    bool isConstructor = false;
    bool isTypeInitializer = false;
    bool isStatic = false;
    bool isEntryPoint = false;
};

