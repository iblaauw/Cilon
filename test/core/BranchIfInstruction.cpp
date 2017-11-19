#include "catch.hpp"

#include "TestClasses.h"

#include "BranchIfInstruction.h"

TEST_CASE_METHOD(StreamTest, "Branch If: Basic", "[BranchIfInstruction]")
{
    LabelInstruction label("mylabel");

    BranchIfInstruction branch(&label);
    branch.Generate(stream);
    REQUIRE(ss.str() == "brtrue mylabel");
}

TEST_CASE_METHOD(StreamTest, "Branch If: Conditions", "[BranchIfInstruction]")
{
    LabelInstruction label("mylabel");

    SECTION("If True")
    {
        BranchIfInstruction branch(&label, true);
        branch.Generate(stream);
        REQUIRE(ss.str() == "brtrue mylabel");
    }

    ResetStream();

    SECTION("If False")
    {
        BranchIfInstruction branch(&label, false);
        branch.Generate(stream);
        REQUIRE(ss.str() == "brfalse mylabel");
    }
}


TEST_CASE("Branch If: Invalid Label", "[BranchIfInstruction][!throws]")
{
    SECTION("Default")
    {
        REQUIRE_THROWS( BranchIfInstruction { nullptr } );
    }

    SECTION("If False")
    {
        REQUIRE_THROWS( BranchIfInstruction ( nullptr, false ) );
    }
}

