#!/usr/bin/python3
import factory

def main():
    add_core_dirs()
    factory.Add("src/main.cpp")
    factory.AddTarget("compiler")

    factory.builtin_rules.CXXFLAGS.append("-std=c++11")
    factory.builtin_rules.CXXFLAGS.append("-Isrc/core")
    factory.builtin_rules.CXXFLAGS.append("-Isrc/generators")
    factory.builtin_rules.CXXFLAGS.append("-g")

    factory.builtin_rules.UseDefaultCppRules()

    factory.Execute()

@factory.special_target("test")
def test(target):
    if target != "clean":
        print("Ensuring the project builds normally...")
        factory.Build(target)

    factory.Reset()

    # Add main source files
    add_core_dirs()

    # Add the test sources in
    factory.AddDir("test/core")
    factory.AddDir("test/end2end")
    factory.AddDir("test/utils")
    factory.Add("test/main.cpp")
    factory.AddTarget("tests")

    # Add main compiler flags
    factory.builtin_rules.CXXFLAGS.append("-std=c++11")
    factory.builtin_rules.CXXFLAGS.append("-Isrc/core")
    factory.builtin_rules.CXXFLAGS.append("-Isrc/generators")
    factory.builtin_rules.CXXFLAGS.append("-Iexternal") # test include for Catch
    factory.builtin_rules.CXXFLAGS.append("-Itest/utils")
    factory.builtin_rules.CXXFLAGS.append("-g")

    factory.builtin_rules.UseDefaultCppRules()

    if target == "clean":
        factory.Clean("tests")
    else:
        factory.Build("tests")

def add_core_dirs():
    factory.AddDir("src/core")
    factory.AddDir("src/generators")
    factory.AddDir("src/builders")

if __name__ == "__main__":
    main()


