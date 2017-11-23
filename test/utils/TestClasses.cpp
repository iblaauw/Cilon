#include "TestClasses.h"

StreamTest::StreamTest()
    : ss(), stream(ss)
{}

void StreamTest::ResetStream()
{
    ss.str(std::string());
}

ILFileTest::ILFileTest()
    : file("mymodule", "myassembly")
{
    currentAssembly = file.GetCurrentAssembly();
    currentModule = currentAssembly->GetCurrentModule();
}

MethodTest::MethodTest()
{
    MethodSignature signature(ILType::GetVoid());
    method = currentModule->GetOrCreateMethod("MyMethod", signature);
}
