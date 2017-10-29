#include "catch.hpp"
#include "Name.h"

TEST_CASE("Identifier determines valid name", "[Identifier]")
{
    SECTION("Simple correct cases")
    {
        REQUIRE( Identifier::IsValidName("Hello") );
        REQUIRE( Identifier::IsValidName("world") );
    }

    SECTION("Specifically allowed complex characters")
    {
        REQUIRE( Identifier::IsValidName("_myName15`@zz") );
        REQUIRE( Identifier::IsValidName("@15??maybE$$7") );
        REQUIRE( Identifier::IsValidName("````???@@@17__893$$") );
    }

    SECTION("Spaces are not allowed")
    {
        REQUIRE_FALSE( Identifier::IsValidName("Hello world") );
        REQUIRE_FALSE( Identifier::IsValidName(" blah") );
        REQUIRE_FALSE( Identifier::IsValidName("yes ") );
    }

    SECTION("Numbers are not allowed at beginning")
    {
        REQUIRE_FALSE( Identifier::IsValidName("5or3?") );
        REQUIRE_FALSE( Identifier::IsValidName("17`2") );
    }

    SECTION("Other common but disallowed characters")
    {
        REQUIRE_FALSE( Identifier::IsValidName("hello.world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello-world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello!world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello^world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello/world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello%world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello<world>") );
        REQUIRE_FALSE( Identifier::IsValidName("hello#world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello&world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello|world") );
        REQUIRE_FALSE( Identifier::IsValidName("helloworld*") );
        REQUIRE_FALSE( Identifier::IsValidName("hello(world)") );
        REQUIRE_FALSE( Identifier::IsValidName("hello~world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello,world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello\\world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello[world]") );
        REQUIRE_FALSE( Identifier::IsValidName("hello{world}") );
        REQUIRE_FALSE( Identifier::IsValidName("hello+world") );
        REQUIRE_FALSE( Identifier::IsValidName("hello'world") );
    }
}
