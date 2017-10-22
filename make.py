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

    factory.builtin_rules.UseDefaultCppRules()

    factory.Execute()

if __name__ == "__main__":
    main()


