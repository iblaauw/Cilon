#include "catch.hpp"
#include <sstream>

#include "ILFile.h"
#include "LoadStringInstruction.h"
#include "CallInstruction.h"
#include "ReturnInstruction.h"
#include "LoadConstantInt.h"
#include "DuplicateInstruction.h"
#include "LabelInstruction.h"
#include "BranchCompareInstruction.h"
#include "NumericInstructions.h"
#include "BranchInstruction.h"
#include "PopInstruction.h"

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
    .maxstack 5
    ldc.i4.0
    loop_start:
    dup
    ldc.i4.s 10
    bge loop_exit
    dup
    call void [mscorlib]System.Console::WriteLine(int32)
    ldc.i4.1
    add
    br loop_start
    loop_exit:
    pop
    ret
}

//*****************************//
// End file MyModule
//*****************************//
)##";

static Method* CreateSystemConsoleWriteline(ILFile& file)
{
    ILType* intType = ILType::GetInt();
    ILType* voidType = ILType::GetVoid();

    MethodSignature funcSignature { voidType };
    funcSignature.AddParameter(intType);

    ExternalAssembly* mscorlib = file.GetOrCreateAssemblyReference("mscorlib");

    ILType* console = mscorlib->GetOrCreateExportedType({"System", "Console"});
    Method* writeline = console->GetOrCreateMethod("WriteLine", funcSignature);
    return writeline;
}

static Method* CreateMainFunction(ILFile& file)
{
    ILType* voidType = ILType::GetVoid();
    MethodSignature mainSignature { voidType }; // void()

    Module* currentModule = file.GetCurrentAssembly()->GetCurrentModule();

    Method* mainFunc = currentModule->GetOrCreateMethod("main", mainSignature);
    mainFunc->SetIsStatic(true);
    mainFunc->SetIsEntryPoint(true);
    mainFunc->SetStackSize(5);

    return mainFunc;
}

TEST_CASE("End-to-end for-loop test", "[end-to-end]")
{
    std::stringstream output;

    ILFile file("MyModule", /*Current assembly*/ "MyAssembly");

    Method* writeline = CreateSystemConsoleWriteline(file);
    Method* main = CreateMainFunction(file);

    std::unique_ptr<LabelInstruction> startLabel = std::make_unique<LabelInstruction>("loop_start");
    std::unique_ptr<LabelInstruction> exitLabel = std::make_unique<LabelInstruction>("loop_exit");

    LabelInstruction* startLabelRef = startLabel.get();
    LabelInstruction* exitLabelRef = exitLabel.get();

    // Preamble
    main->AddInstruction(std::make_unique<LoadConstantInt>(0));

    // Comparison
    main->AddInstruction(std::move(startLabel));
    main->AddInstruction(std::make_unique<DuplicateInstruction>());
    main->AddInstruction(std::make_unique<LoadConstantInt>(10));
    main->AddInstruction(std::make_unique<BranchCompareInstruction>(exitLabelRef, FullComparison::GreaterOrEqual));

    // Main body
    // - call writeline
    // - add one to 'i'
    // - go to the top of the loop
    main->AddInstruction(std::make_unique<DuplicateInstruction>());
    main->AddInstruction(std::make_unique<CallInstruction>(writeline));
    main->AddInstruction(std::make_unique<LoadConstantInt>(1));
    main->AddInstruction(std::make_unique<AddInstruction>());
    main->AddInstruction(std::make_unique<BranchInstruction>(startLabelRef));

    // Exit
    main->AddInstruction(std::move(exitLabel));
    main->AddInstruction(std::make_unique<PopInstruction>());
    main->AddInstruction(std::make_unique<ReturnInstruction>());

    // Generate the file
    file.Generate(output);

    REQUIRE(output.str() == correctOutput);
}



