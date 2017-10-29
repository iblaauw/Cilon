#include <iostream>

#include "ILFile.h"
#include "LoadStringInstruction.h"
#include "CallInstruction.h"
#include "ReturnInstruction.h"

int main()
{
    auto& output = std::cout;

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

    auto loadstr2 = std::make_unique<LoadStringInstruction>("Hello Eric :D");
    mainFunc->AddInstruction(std::move(loadstr2));

    auto callInstr2 = std::make_unique<CallInstruction>(writeline);
    mainFunc->AddInstruction(std::move(callInstr2));

    auto retInstr = std::make_unique<ReturnInstruction>();
    mainFunc->AddInstruction(std::move(retInstr));

    // Create a new class
    ILType* customType = currentModule->GetOrCreateType("MyType");

    // Echo function
    MethodSignature echoSignature { stringType };
    funcSignature.AddParameter(stringType);

    Method* echoFunc = customType->GetOrCreateMethod("Echo", echoSignature);
    echoFunc->SetStackSize(1);
    echoFunc->AddInstruction(std::make_unique<LoadStringInstruction>("echo"));
    echoFunc->AddInstruction(std::make_unique<ReturnInstruction>());

    // Generate the file
    file.Generate(output);
    return 0;
}

