#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <initializer_list>

// This class keeps what a valid identifier is in IL
class Identifier final
{
public:
    Identifier(std::string name);
    Identifier(const char* name);

    static bool IsValidName(std::string name);

    std::string GetString() const { return name; }

    // Output operator
    friend std::ostream& operator<<(std::ostream& out, const Identifier& name);
private:
    std::string name;
};

// The goal of this class is to easily create dotted names out of identifiers
// Each time add is called, another piece of the name is added,
// a '.' is used to join them
class Name final
{
public:
    Name() = default;
    Name(std::string name);
    Name(const char* name);
    Name(std::initializer_list<const char*> init_list);
    explicit Name(const Identifier& id);

    void Add(std::string piece);
    void Add(const Identifier& id);
    void Add(const char* piece);

    bool empty() const
    {
        return namePieces.size() == 0;
    }

    std::string GetString() const;

    friend std::ostream& operator<<(std::ostream& out, const Name& name);
private:
    std::vector<std::string> namePieces;
};

class InvalidIdentifierException : public std::invalid_argument
{
public:
    // Inherit base class constructors
    using std::invalid_argument::invalid_argument;
};

std::ostream& operator<<(std::ostream& out, const Identifier& name);
std::ostream& operator<<(std::ostream& out, const Name& name);



