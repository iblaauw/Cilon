#include "catch.hpp"
#include <sstream>

#include "NumericInstructions.h"

TEST_CASE("Add", "[NumericInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    AddInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "add");
}

TEST_CASE("Subtract", "[NumericInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    SubtractInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "sub");
}

TEST_CASE("Multiply", "[NumericInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    MultiplyInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "mul");
}

TEST_CASE("Divide", "[NumericInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    DivideInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "div");
}

TEST_CASE("Negate", "[NumericInstructions]")
{
    std::stringstream ss;
    Stream stream(ss);

    NegateInstruction instr {};
    instr.Generate(stream);

    REQUIRE(ss.str() == "neg");
}

