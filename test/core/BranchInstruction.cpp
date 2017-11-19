#include "catch.hpp"

#include "TestClasses.h"

#include "LabelInstruction.h"
#include "BranchInstruction.h"

TEST_CASE_METHOD(StreamTest, "Branch: Basic", "[BranchInstruction]")
{
    LabelInstruction label("mylabel");
    BranchInstruction branch(&label);

    branch.Generate(stream);
    REQUIRE(ss.str() == "br mylabel");
}

TEST_CASE("Branch: Invalid Label", "[BranchInstruction][!throws]")
{
    REQUIRE_THROWS( BranchInstruction { nullptr } );
}

