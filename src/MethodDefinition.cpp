#include "MethodDefinition.h"

#include "ILType.h"

MethodDefinition::MethodDefinition(Name name, std::shared_ptr<FunctionSignature> signature)
    : MethodReference(name, signature, nullptr), stackSize(0), isEntryPoint(false)
{
}

void MethodDefinition::AddInstruction(std::unique_ptr<ILInstruction> instr)
{
    instructions.emplace_back(std::move(instr));
}

void MethodDefinition::Generate(std::ostream& out) const
{
    // Output method header
    out << ".method";
    if (isStatic)
    {
        out << " static";
    }
    out << " public " << *signature->GetReturnType() << ' ' << name;
    signature->GenerateParamList(out);
    out << " cil managed" << std::endl;

    out << '{' << std::endl;

    // Output function metadata
    if (isEntryPoint)
    {
        out << "    .entrypoint" << std::endl;
    }

    out << "    .maxstack " << stackSize << std::endl;

    // Output Instructions
    for (auto& instr : instructions)
    {
        out << "    ";
        instr->Generate(out);
    }

    out << '}' << std::endl;
}



/*
#include "LoadStringInstruction.h"
#include "CallInstruction.h"
#include "ReturnInstruction.h"

MethodDefinition::MethodDefinition(std::string name)
    : name(name)
{}

void MethodDefinition::PreGenerate(std::ostream& out) const
{
    out << ".method static public void " << name << "() cil managed" << std::endl;
    out << "{" << std::endl;

    if (isEntryPoint)
    {
        out << "    .entrypoint" << std::endl;
    }

    out << "    .maxstack " << stackSize << std::endl;
}

void MethodDefinition::PostGenerate(std::ostream& out) const
{
    out << "}" << std::endl;
}

const TypeSet& MethodDefinition::GetValidChildTypes() const
{
    static TypeSet typeSet = CreateTypeSet<
        LoadStringInstruction,
        CallInstruction,
        ReturnInstruction>();
    return typeSet;
}
*/

