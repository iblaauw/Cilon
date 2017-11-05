#include "catch.hpp"

#include "ILType.h"

TEST_CASE("int32", "[BuiltinType]")
{
    ILType* intType = ILType::GetInt();
    REQUIRE(intType != nullptr);
    REQUIRE(intType->GetName().GetString() == "int32");
    REQUIRE(intType->IsBuiltin());
}

TEST_CASE("bool", "[BuiltinType]")
{
    ILType* type = ILType::GetBool();
    REQUIRE(type != nullptr);
    REQUIRE(type->GetName().GetString() == "bool");
    REQUIRE(type->IsBuiltin());
}

TEST_CASE("string", "[BuiltinType]")
{
    ILType* type = ILType::GetString();
    REQUIRE(type != nullptr);
    REQUIRE(type->GetName().GetString() == "string");
    REQUIRE(type->IsBuiltin());
}

TEST_CASE("void", "[BuiltinType]")
{
    ILType* type = ILType::GetVoid();
    REQUIRE(type != nullptr);
    REQUIRE(type->GetName().GetString() == "void");
    REQUIRE(type->IsBuiltin());
}

TEST_CASE("object", "[BuiltinType]")
{
    ILType* type = ILType::GetObject();
    REQUIRE(type != nullptr);
    REQUIRE(type->GetName().GetString() == "object");
    REQUIRE(type->IsBuiltin());
}

