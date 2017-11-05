#include "catch.hpp"
#include <sstream>

#include "BitwiseInstructions.h"

TEST_CASE("And", "[BitwiseInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    AndInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "and");
}

TEST_CASE("Or", "[BitwiseInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    OrInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "or");
}

TEST_CASE("XOr", "[BitwiseInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    XOrInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "xor");
}

TEST_CASE("ShiftLeft", "[BitwiseInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    ShiftLeftInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "shl");
}

TEST_CASE("ShiftRight", "[BitwiseInstructions]")
{
    SECTION("Signed")
    {
        std::stringstream ss;
        Stream stream(ss);

        ShiftRightInstruction instr {};
        instr.Generate(stream);

        REQUIRE(ss.str() == "shr");
    }

    SECTION("Unsigned")
    {
        std::stringstream ss;
        Stream stream(ss);

        ShiftRightInstruction instr {};
        instr.SetIsUnsigned(true);
        instr.Generate(stream);

        REQUIRE(ss.str() == "shr.un");
    }
}



