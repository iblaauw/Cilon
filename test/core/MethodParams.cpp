#include "catch.hpp"
#include <sstream>

#include "ILFile.h"
#include "Method.h"
#include "MethodDefGenerator.h"

class MethodParamsTestHelper
{
public:
    MethodParamsTestHelper()
        : file("test.exe", "TestAssembly"), ss(), stream(ss)
    {
        assembly = file.GetCurrentAssembly();
        module = assembly->GetCurrentModule();
    }

    template <class... Args>
    Method* CreateMethod(const Name& name, Args... args)
    {
        ILType* voidType = ILType::GetVoid();
        MethodSignature methodSignature { voidType };
        std::vector<ILType*> vec = { args... };
        for (ILType* type : vec)
        {
            methodSignature.AddParameter(type);
        }

        return module->GetOrCreateMethod(name, methodSignature);
    }

    ILFile file;
    InternalAssembly* assembly;
    Module* module;
    std::stringstream ss;
    Stream stream;
};

TEST_CASE_METHOD(MethodParamsTestHelper, "Basic Method Parameters", "[MethodParams]")
{
    ILType* intType = ILType::GetInt();
    ILType* stringType = ILType::GetString();
    Method* method = CreateMethod("MyMethod", intType, stringType);

    MethodDefParamsGenerator generator { method };
    generator.Generate(stream);

    REQUIRE(ss.str() == "int32, string");
}

// TODO: this belongs in a different test case
TEST_CASE_METHOD(MethodParamsTestHelper, "Void method parameter", "[MethodParams][!throws][!mayfail]")
{
    ILType* voidType = ILType::GetVoid();
    REQUIRE_THROWS(CreateMethod("MyMethod", voidType));
}

TEST_CASE_METHOD(MethodParamsTestHelper, "Method Parameter Name: simple", "[MethodParams]")
{
    ILType* intType = ILType::GetInt();
    ILType* stringType = ILType::GetString();
    Method* method = CreateMethod("MyMethod", intType, stringType);
    method->SetParamName(0, "hi");
    method->SetParamName(1, "everyone");

    MethodDefParamsGenerator generator { method };
    generator.Generate(stream);

    REQUIRE(ss.str() == "int32 hi, string everyone");
}

TEST_CASE_METHOD(MethodParamsTestHelper, "Method Parameter Name: mixed", "[MethodParams]")
{
    ILType* intType = ILType::GetInt();
    ILType* stringType = ILType::GetString();
    Method* method = CreateMethod("MyMethod", intType, stringType, intType);

    SECTION("Setting params")
    {
        method->SetParamName(0, "hi");
        method->SetParamName(2, "everyone");

        MethodDefParamsGenerator generator { method };
        generator.Generate(stream);

        REQUIRE(ss.str() == "int32 hi, string, int32 everyone");
    }

    SECTION("Unsetting params")
    {
        method->UnsetParamName(0);
        method->SetParamName(1, "center");
        method->UnsetParamName(2);

        MethodDefParamsGenerator generator { method };
        generator.Generate(stream);

        REQUIRE(ss.str() == "int32, string center, int32");
    }
}

TEST_CASE_METHOD(MethodParamsTestHelper, "Method Parameter Name: invalid name", "[MethodParams][!throws]")
{
    ILType* intType = ILType::GetInt();
    Method* method = CreateMethod("MyMethod", intType);
    REQUIRE_THROWS(method->SetParamName(0, "hello.world"));
}

TEST_CASE_METHOD(MethodParamsTestHelper, "Method Parameter Name: invalid index", "[MethodParams][!throws]")
{
    ILType* intType = ILType::GetInt();
    ILType* stringType = ILType::GetString();
    Method* method = CreateMethod("MyMethod", intType, stringType, intType);

    SECTION("Unset")
    {
        REQUIRE_THROWS(method->GetParamName(0));
        REQUIRE_THROWS(method->GetParamName(1));
        REQUIRE_THROWS(method->GetParamName(2));
    }

    method->SetParamName(0, "a");
    method->SetParamName(2, "c");

    SECTION("Unset 2")
    {
        REQUIRE_THROWS(method->GetParamName(1));
    }

    method->SetParamName(1, "b");

    SECTION("Negative")
    {
        REQUIRE_THROWS(method->GetParamName(-1));
        REQUIRE_THROWS(method->SetParamName(-2, "hi"));
        REQUIRE_THROWS(method->UnsetParamName(-3));
    }

    SECTION("Over")
    {
        REQUIRE_THROWS(method->GetParamName(3));
        REQUIRE_THROWS(method->SetParamName(4, "hi"));
        REQUIRE_THROWS(method->UnsetParamName(5));
    }
}


