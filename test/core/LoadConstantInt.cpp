#include "catch.hpp"
#include <sstream>

#include "LoadConstantInt.h"
#include "ILFile.h"

TEST_CASE("Basic load constant int", "[LoadConstantInt]")
{
    SECTION("Positive 1000")
    {
        std::stringstream ss;
        Stream stream(ss);

        LoadConstantInt load(1000);
        load.Generate(stream);

        REQUIRE(ss.str() == "ldc.i4 1000");
    }

    SECTION("Negative 1000")
    {
        std::stringstream ss;
        Stream stream(ss);

        LoadConstantInt load(-1000);
        load.Generate(stream);

        REQUIRE(ss.str() == "ldc.i4 -1000");
    }
}

TEST_CASE("LoadConstantInt predefined shortforms", "[LoadConstantInt]")
{
    std::stringstream ss;
    Stream stream(ss);

    SECTION("0")
    {
        LoadConstantInt load(0);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.0");
        ss.str(std::string());
    }

    SECTION("1")
    {
        LoadConstantInt load(1);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.1");
        ss.str(std::string());
    }

    SECTION("2")
    {
        LoadConstantInt load(2);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.2");
        ss.str(std::string());
    }

    SECTION("3")
    {
        LoadConstantInt load(3);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.3");
        ss.str(std::string());
    }

    SECTION("4")
    {
        LoadConstantInt load(4);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.4");
        ss.str(std::string());
    }

    SECTION("5")
    {
        LoadConstantInt load(5);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.5");
        ss.str(std::string());
    }

    SECTION("6")
    {
        LoadConstantInt load(6);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.6");
        ss.str(std::string());
    }

    SECTION("7")
    {
        LoadConstantInt load(7);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.7");
        ss.str(std::string());
    }

    SECTION("8")
    {
        LoadConstantInt load(8);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.8");
        ss.str(std::string());
    }

    SECTION("-1")
    {
        LoadConstantInt load(-1);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.m1");
        ss.str(std::string());
    }
}

TEST_CASE("LoadConstantInt shortform", "[LoadConstantInt]")
{
    std::stringstream ss;
    Stream stream(ss);

    SECTION("117")
    {
        LoadConstantInt load(117);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.s 117");
        ss.str(std::string());
    }

    SECTION("-98")
    {
        LoadConstantInt load(-98);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.s -98");
        ss.str(std::string());
    }

    SECTION("127")
    {
        LoadConstantInt load(127);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.s 127");
        ss.str(std::string());
    }

    SECTION("128")
    {
        LoadConstantInt load(128);
        load.Generate(stream);
        REQUIRE(ss.str() != "ldc.i4.s 128");
        ss.str(std::string());
    }

    SECTION("-128")
    {
        LoadConstantInt load(-128);
        load.Generate(stream);
        REQUIRE(ss.str() == "ldc.i4.s -128");
        ss.str(std::string());
    }

    SECTION("-129")
    {
        LoadConstantInt load(-129);
        load.Generate(stream);
        REQUIRE(ss.str() != "ldc.i4.s -129");
        ss.str(std::string());
    }
}

TEST_CASE("LoadConstnatInt real use", "[LoadConstantInt]")
{
    ILFile ilfile("test_module", "test_assembly");
    InternalAssembly* assembly = ilfile.GetCurrentAssembly();
    Module* module = assembly->GetCurrentModule();

    MethodSignature signature { ILType::GetVoid() };
    Method* method = module->GetOrCreateMethod("TestMethod", signature);

    std::unique_ptr<LoadConstantInt> loadInstr = std::make_unique<LoadConstantInt>(50);
    REQUIRE_NOTHROW(method->AddInstruction(std::move(loadInstr)));
}

