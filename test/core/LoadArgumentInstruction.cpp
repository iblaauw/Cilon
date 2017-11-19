#include "catch.hpp"

#include "TestClasses.h"

#include "LoadArgumentInstruction.h"

TEST_CASE_METHOD(StreamTest, "Load Arg: Basic", "[LoadArgumentInstruction]")
{
    LoadArgumentInstruction loadArg(350);
    loadArg.Generate(stream);
    REQUIRE(ss.str() == "ldarg 350");
}

TEST_CASE_METHOD(StreamTest, "Load Arg: Builtins forms", "[LoadArgumentInstruction]")
{
    SECTION("0")
    {
        LoadArgumentInstruction loadArg(0);
        loadArg.Generate(stream);
        REQUIRE(ss.str() == "ldarg.0");
    }

    ResetStream();

    SECTION("1")
    {
        LoadArgumentInstruction loadArg(1);
        loadArg.Generate(stream);
        REQUIRE(ss.str() == "ldarg.1");
    }

    ResetStream();

    SECTION("2")
    {
        LoadArgumentInstruction loadArg(2);
        loadArg.Generate(stream);
        REQUIRE(ss.str() == "ldarg.2");
    }

    ResetStream();

    SECTION("3")
    {
        LoadArgumentInstruction loadArg(3);
        loadArg.Generate(stream);
        REQUIRE(ss.str() == "ldarg.3");
    }
}

TEST_CASE_METHOD(StreamTest, "Load Arg: Shortform", "[LoadArgumentInstruction]")
{
    SECTION("4")
    {
        LoadArgumentInstruction loadArg(4);
        loadArg.Generate(stream);
        REQUIRE(ss.str() == "ldarg.s 4");
    }

    SECTION("255")
    {
        LoadArgumentInstruction loadArg(255);
        loadArg.Generate(stream);
        REQUIRE(ss.str() == "ldarg.s 255");
    }

    SECTION("154")
    {
        LoadArgumentInstruction loadArg(154);
        loadArg.Generate(stream);
        REQUIRE(ss.str() == "ldarg.s 154");
    }
}

TEST_CASE_METHOD(StreamTest, "Load Arg: Invalid", "[LoadArgumentInstruction][!throws]")
{
    SECTION("-1")
    {
        REQUIRE_THROWS( LoadArgumentInstruction { -1 } );
    }

    SECTION("-10")
    {
        REQUIRE_THROWS( LoadArgumentInstruction { -10 } );
    }
}

TEST_CASE_METHOD(StreamTest, "Load Arg: Name", "[LoadArgumentInstruction]")
{
    LoadArgumentInstruction loadArg("myparamname");
    loadArg.Generate(stream);
    REQUIRE(ss.str() == "ldarg myparamname");
}

TEST_CASE_METHOD(StreamTest, "Load Arg: Invalid Name", "[LoadArgumentInstruction][!throws]")
{
    REQUIRE_THROWS( LoadArgumentInstruction { "my.param.name" } );
}


