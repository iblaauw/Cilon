#include "catch.hpp"

#include "TestClasses.h"

#include "ILFile.h"
#include "Method.h"
#include "LocalsGenerator.h"
#include "MethodDefGenerator.h"

TEST_CASE_METHOD(MethodTest, "Locals: Basic", "[LocalVariables]")
{
    ILType* intType = ILType::GetInt();
    ILType* stringType = ILType::GetString();
    method->Locals().Add(intType, "my");
    method->Locals().Add(stringType, "variable");

    LocalsGenerator generator { method->Locals() };
    generator.Generate(stream);

    REQUIRE(ss.str() == ".locals init (int32 my, string variable)");

    ResetStream();

    MethodDefGenerator methodGenerator(method);
    methodGenerator.Generate(stream);
    REQUIRE_THAT(ss.str(), Catch::Contains(".locals init (int32 my, string variable)"));
}

TEST_CASE_METHOD(MethodTest, "Locals: No Void", "[LocalVariables][!throws]")
{
    ILType* voidType = ILType::GetVoid();
    REQUIRE_THROWS( method->Locals().Add(voidType) );
    REQUIRE_THROWS( method->Locals().Add(voidType, "hi") );
}

TEST_CASE_METHOD(MethodTest, "Locals: Mixed", "[LocalVariables]")
{
    ILType* intType = ILType::GetInt();
    ILType* stringType = ILType::GetString();

    auto& locals = method->Locals();
    locals.Add(intType, "hello");
    locals.Add(intType);
    locals.Add(stringType, "world");

    REQUIRE(!locals.HasName(1));

    LocalsGenerator generator { locals };
    generator.Generate(stream);

    REQUIRE(ss.str() == ".locals init (int32 hello, int32, string world)");
}

TEST_CASE_METHOD(MethodTest, "Locals: Invalid Unset Name", "[LocalVariables][!throws]")
{
    ILType* intType = ILType::GetInt();
    auto& locals = method->Locals();
    locals.Add(intType);

    REQUIRE_THROWS(locals.GetName(0));
}

TEST_CASE_METHOD(MethodTest, "Locals: Invalid Index", "[LocalVariables][!throws]")
{
    ILType* intType = ILType::GetInt();
    auto& locals = method->Locals();

    SECTION("0")
    {
        REQUIRE_THROWS(locals.HasName(0));
        REQUIRE_THROWS(locals.GetName(0));
        REQUIRE_THROWS(locals.GetType(0));
    }

    locals.Add(intType);
    locals.Add(intType);

    SECTION("2")
    {
        REQUIRE_THROWS(locals.HasName(2));
        REQUIRE_THROWS(locals.GetName(2));
        REQUIRE_THROWS(locals.GetType(2));
    }

    SECTION("-1")
    {
        REQUIRE_THROWS(locals.HasName(-1));
        REQUIRE_THROWS(locals.GetName(-1));
        REQUIRE_THROWS(locals.GetType(-1));
    }
}

