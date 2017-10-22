#include <iostream>

#include "ILFile.h"
#include "LoadStringInstruction.h"
#include "CallInstruction.h"
#include "ReturnInstruction.h"

#include "TypeGenerator.h"

int main()
{
    auto& output = std::cout;

    /*TypeGenerator gen { ILType::GetVoid() };
    gen.Generate(output);
    return 0;*/

    ILFile file("MyModule", /*Current assembly*/ "MyAssembly");

    ExternalAssembly* mscorlib = file.GetOrCreateAssemblyReference("mscorlib");

    ILType* voidType = ILType::GetVoid();
    MethodSignature mainSignature { voidType }; // void()

    Module* currentModule = file.GetCurrentAssembly()->GetCurrentModule();

    // Create main function
    Method* mainFunc = currentModule->GetOrCreateMethod("main", mainSignature);
    mainFunc->SetIsStatic(true);
    mainFunc->SetIsEntryPoint(true);
    mainFunc->SetStackSize(1);

    // Load a string
    auto loadstr = std::make_unique<LoadStringInstruction>("Hello World! Hi!!!!!");
    mainFunc->AddInstruction(std::move(loadstr));

    // Call a function
    ILType* stringType = ILType::GetString();
    MethodSignature funcSignature { voidType };
    funcSignature.AddParameter(stringType);

    ILType* console = mscorlib->GetOrCreateExportedType({"System", "Console"});
    Method* writeline = console->GetOrCreateMethod("WriteLine", funcSignature);

    auto callInstr = std::make_unique<CallInstruction>(writeline);
    mainFunc->AddInstruction(std::move(callInstr));

    auto retInstr = std::make_unique<ReturnInstruction>();
    mainFunc->AddInstruction(std::move(retInstr));

    // Generate the file
    file.Generate(output);
    return 0;
}

