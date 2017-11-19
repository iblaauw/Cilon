#include "catch.hpp"

#include "TestClasses.h"

#include "LabelInstruction.h"

TEST_CASE_METHOD(StreamTest, "Label: Basic", "[LabelInstruction]")
{
    LabelInstruction label("mylabelname");
    label.Generate(stream);
    REQUIRE(ss.str() == "mylabelname:");
}

TEST_CASE("Label: Invalid Name", "[LabelInstruction][!throws]")
{
    REQUIRE_THROWS( LabelInstruction { "my.invalidname" } );
}

