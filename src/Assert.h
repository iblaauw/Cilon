#pragma once

#include <stdexcept>

class AssertionException : std::runtime_error
{
public:
    AssertionException(std::string message) : std::runtime_error(message) {}
};

// Standard assert
void Assert(bool value, std::string message)
{
    if (!value)
        throw AssertionException(message);
}

