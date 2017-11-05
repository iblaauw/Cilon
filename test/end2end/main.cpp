#include "catch.hpp"
#include <sstream>

#include "ILFile.h"
#include "LoadStringInstruction.h"
#include "CallInstruction.h"
#include "ReturnInstruction.h"
#include "LoadNullInstruction.h"

static const char* correctOutput = 
R"##(//*****************************//
// Begin file MyModule
//*****************************//
.assembly extern mscorlib {}
.assembly MyAssembly{}

.module MyModule

.method static public void main() cil managed
{
    .entrypoint
    .maxstack 1
    ldstr "Hello World! Hi!!!!!"
    call void [mscorlib]System.Console::WriteLine(string)
    ldstr "Hello Eric :D"
    call void [mscorlib]System.Console::WriteLine(string)
    ret
}

.class private auto ansi MyType
{
    .method static public class MyType Create() cil managed
    {
        .maxstack 1
        ldnull
        ret
    }

    .method public string Echo(string) cil managed
    {
        .maxstack 1
        ldstr "echo"
        ret
    }

}
//*****************************//
// End file MyModule
//*****************************//
)##";

TEST_CASE("Large end-to-end test", "[end-to-end]")
{
    std::stringstream output;

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
    echoSignature.AddParameter(stringType);

    Method* echoFunc = customType->GetOrCreateMethod("Echo", echoSignature);
    echoFunc->SetStackSize(1);
    echoFunc->AddInstruction(std::make_unique<LoadStringInstruction>("echo"));
    echoFunc->AddInstruction(std::make_unique<ReturnInstruction>());

    // Create Function
    MethodSignature createSignature { customType };
    Method* createFunc = customType->GetOrCreateMethod("Create", createSignature);
    createFunc->SetIsStatic(true);
    createFunc->SetStackSize(1);
    createFunc->AddInstruction(std::make_unique<LoadNullInstruction>());
    createFunc->AddInstruction(std::make_unique<ReturnInstruction>());

    // Generate the file
    file.Generate(output);

    REQUIRE(output.str() == correctOutput);
}



