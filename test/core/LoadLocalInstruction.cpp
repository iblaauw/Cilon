#include "catch.hpp"

#include "TestClasses.h"

#include "LoadLocalInstruction.h"

TEST_CASE_METHOD(StreamTest, "Load Local: Basic", "[LoadLocalInstruction]")
{
    LoadLocalInstruction loadLoc(342);
    loadLoc.Generate(stream);
    REQUIRE(ss.str() == "ldloc 342");
}

TEST_CASE_METHOD(StreamTest, "Load Local: Builtins forms", "[LoadLocalInstruction]")
{
    SECTION("0")
    {
        LoadLocalInstruction loadLoc(0);
        loadLoc.Generate(stream);
        REQUIRE(ss.str() == "ldloc.0");
    }

    ResetStream();

    SECTION("1")
    {
        LoadLocalInstruction loadLoc(1);
        loadLoc.Generate(stream);
        REQUIRE(ss.str() == "ldloc.1");
    }

    ResetStream();

    SECTION("2")
    {
        LoadLocalInstruction loadLoc(2);
        loadLoc.Generate(stream);
        REQUIRE(ss.str() == "ldloc.2");
    }

    ResetStream();

    SECTION("3")
    {
        LoadLocalInstruction loadLoc(3);
        loadLoc.Generate(stream);
        REQUIRE(ss.str() == "ldloc.3");
    }
}

TEST_CASE_METHOD(StreamTest, "Load Local: Shortform", "[LoadLocalInstruction]")
{
    SECTION("4")
    {
        LoadLocalInstruction loadLoc(4);
        loadLoc.Generate(stream);
        REQUIRE(ss.str() == "ldloc.s 4");
    }

    ResetStream();

    SECTION("255")
    {
        LoadLocalInstruction loadLoc(255);
        loadLoc.Generate(stream);
        REQUIRE(ss.str() == "ldloc.s 255");
    }

    ResetStream();

    SECTION("154")
    {
        LoadLocalInstruction loadLoc(154);
        loadLoc.Generate(stream);
        REQUIRE(ss.str() == "ldloc.s 154");
    }
}

TEST_CASE_METHOD(StreamTest, "Load Local: Invalid", "[LoadLocalInstruction][!throws]")
{
    SECTION("-1")
    {
        REQUIRE_THROWS( LoadLocalInstruction { -1 } );
    }

    SECTION("-10")
    {
        REQUIRE_THROWS( LoadLocalInstruction { -10 } );
    }
}

TEST_CASE_METHOD(StreamTest, "Load Local: Maximum Value", "[LoadLocalInstruction][!throws][!mayfail]")
{
    REQUIRE_THROWS( LoadLocalInstruction { 1 << 16 } );
}

TEST_CASE_METHOD(StreamTest, "Load Local: Name", "[LoadLocalInstruction]")
{
    LoadLocalInstruction loadLoc("myvariablename");
    loadLoc.Generate(stream);
    REQUIRE(ss.str() == "ldloc myvariablename");
}

TEST_CASE_METHOD(StreamTest, "Load Local: Invalid Name", "[LoadLocalInstruction][!throws]")
{
    REQUIRE_THROWS( LoadLocalInstruction { "my.var.name" } );
}


