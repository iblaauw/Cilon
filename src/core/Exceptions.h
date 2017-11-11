#pragma once

#include <stdexcept>

class AssertionException : std::runtime_error
{
public:
    AssertionException(std::string message) : std::runtime_error(message) {}
};

/*// Standard assert
void Assert(bool value, std::string message)
{
    if (!value)
        throw AssertionException(message);
}*/

class NullArgumentException : std::runtime_error
{
public:
    NullArgumentException(std::string message) : std::runtime_error(message) {}
};

class InvalidArgumentException : std::runtime_error
{
public:
    InvalidArgumentException(std::string message) : std::runtime_error(message) {}
};

class InvalidOperationException : std::runtime_error
{
public:
    InvalidOperationException(std::string message) : std::runtime_error(message) {}
};

class NotImplementedException : std::runtime_error
{
public:
    NotImplementedException() : std::runtime_error("Not Implemented") {}
};

class IndexOutOfRangeException : std::runtime_error
{
public:
    IndexOutOfRangeException(std::string message) : std::runtime_error(message) {}
};


