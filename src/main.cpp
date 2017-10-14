#include <iostream>

#include "ILFile.h"
#include "AssemblyReference.h"
#include "AssemblyDeclaration.h"
#include "MethodDefinition.h"
#include "LoadStringInstruction.h"
#include "CallInstruction.h"
#include "ReturnInstruction.h"
#include "Utils.h"

int main()
{
    auto& output = std::cout;

    ILFile file("test.il", /*Current assembly*/ "MyAssembly");

    Assembly* mscorlib = file.CreateReference("mscorlib");

    ILType* voidType = ILType::GetVoid();
    std::shared_ptr<FunctionSignature> mainSignature = std::make_shared<FunctionSignature>(voidType);

    // Create main function
    MethodDefinition* mainFunc = file.CreateMethod("main", mainSignature);
    mainFunc->SetIsStatic(true);
    mainFunc->SetIsEntryPoint(true);
    mainFunc->SetStackSize(1);

    // Load a string
    auto loadstr = std::make_unique<LoadStringInstruction>("Hello World! Hi!!!!!");
    mainFunc->AddInstruction(std::move(loadstr));

    // Call a function
    ILType* stringType = ILType::GetString();
    std::shared_ptr<FunctionSignature> funcSignature = std::make_shared<FunctionSignature>(voidType, stringType);

    ILType* console = mscorlib->GetType({"System", "Console"});
    MethodReference* writeline = console->GetMethod("WriteLine", funcSignature);

    auto callInstr = std::make_unique<CallInstruction>(writeline);
    mainFunc->AddInstruction(std::move(callInstr));

    auto retInstr = std::make_unique<ReturnInstruction>();
    mainFunc->AddInstruction(std::move(retInstr));

    // Generate the file
    file.Generate(output);
}

