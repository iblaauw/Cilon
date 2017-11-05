#!/usr/bin/python3
import factory

def main():
    factory.AddDir("src/core")
    factory.AddDir("src/generators")
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
    factory.AddDir("src/core")
    factory.AddDir("src/generators")

    # Add the test sources in
    factory.AddDir("test/core")
    #factory.AddDir("test/generators")
    factory.Add("test/main.cpp")
    factory.AddTarget("tests")

    # Add main compiler flags
    factory.builtin_rules.CXXFLAGS.append("-std=c++11")
    factory.builtin_rules.CXXFLAGS.append("-Isrc/core")
    factory.builtin_rules.CXXFLAGS.append("-Isrc/generators")
    factory.builtin_rules.CXXFLAGS.append("-Iexternal") # test include for Catch
    factory.builtin_rules.CXXFLAGS.append("-g")

    factory.builtin_rules.UseDefaultCppRules()

    if target == "clean":
        factory.Clean("tests")
    else:
        factory.Build("tests")

if __name__ == "__main__":
    main()


