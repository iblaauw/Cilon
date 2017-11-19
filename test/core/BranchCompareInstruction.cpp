#include "catch.hpp"

#include "TestClasses.h"

#include "BranchCompareInstruction.h"


TEST_CASE_METHOD(StreamTest, "Branch Compare: Basic", "[BranchCompareInstruction]")
{
    LabelInstruction label("mylabel");

    SECTION("Less-Than")
    {
        BranchCompareInstruction branch(&label, FullComparison::LessThan);
        branch.Generate(stream);
        REQUIRE(ss.str() == "blt mylabel");
    }

    ResetStream();

    SECTION("Less-Equal")
    {
        BranchCompareInstruction branch(&label, FullComparison::LessOrEqual);
        branch.Generate(stream);
        REQUIRE(ss.str() == "ble mylabel");
    }

    ResetStream();

    SECTION("Greater-Than")
    {
        BranchCompareInstruction branch(&label, FullComparison::GreaterThan);
        branch.Generate(stream);
        REQUIRE(ss.str() == "bgt mylabel");
    }

    ResetStream();

    SECTION("Greater-Equal")
    {
        BranchCompareInstruction branch(&label, FullComparison::GreaterOrEqual);
        branch.Generate(stream);
        REQUIRE(ss.str() == "bge mylabel");
    }

    ResetStream();

    SECTION("Equal")
    {
        BranchCompareInstruction branch(&label, FullComparison::Equal);
        branch.Generate(stream);
        REQUIRE(ss.str() == "beq mylabel");
    }

    ResetStream();

    SECTION("Not Equal")
    {
        BranchCompareInstruction branch(&label, FullComparison::NotEqual);
        branch.Generate(stream);
        REQUIRE(ss.str() == "bne.un mylabel");
    }
}

TEST_CASE_METHOD(StreamTest, "Branch Compare: Using non-full comparison type", "[BranchCompareInstruction]")
{
    LabelInstruction label("mylabel");

    SECTION("Less-Than")
    {
        BranchCompareInstruction branch(&label, Comparison::LessThan);
        branch.Generate(stream);
        REQUIRE(ss.str() == "blt mylabel");
    }

    ResetStream();

    SECTION("Greater-Than")
    {
        BranchCompareInstruction branch(&label, Comparison::GreaterThan);
        branch.Generate(stream);
        REQUIRE(ss.str() == "bgt mylabel");
    }

    ResetStream();

    SECTION("Equal")
    {
        BranchCompareInstruction branch(&label, Comparison::Equal);
        branch.Generate(stream);
        REQUIRE(ss.str() == "beq mylabel");
    }
}

TEST_CASE("Branch Compare: Invalid Label", "[BranchCompareInstruction][!throws]")
{
    REQUIRE_THROWS( BranchCompareInstruction( nullptr, Comparison::GreaterThan ) );
}

