#include "Name.h"

#include <sstream>

#include "Utils.h"

Identifier::Identifier(std::string name)
{
    if (!IsValidName(name))
        throw InvalidIdentifierException(Format("Invalid identifier: ", name));

    this->name = name;
}

Identifier::Identifier(const char* name)
    : Identifier(std::string(name))
{}

static bool isalpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}

static bool isnumeric(char c)
{
    return (c >= '0' && c <= '9');
}

static bool isspecial(char c)
{
    return c == '`' ||
           c == '_' ||
           c == '@' ||
           c == '$' ||
           c == '?';
}

/*static*/ bool Identifier::IsValidName(std::string name)
{
    if (name.length() == 0)
        return false;

    char c1 = name[0];
    if (!isalpha(c1) && !isspecial(c1))
        return false;

    for (char c : name)
    {
        if (!isalpha(c) && !isnumeric(c) && !isspecial(c))
            return false;
    }

    return true;
}

Name::Name(std::string name)
{
    Add(name);
}

Name::Name(const char* name)
    : Name(std::string(name))
{
}

Name::Name(std::initializer_list<const char*> init_list)
{
    for (auto str : init_list)
    {
        Add(str);
    }
}

Name::Name(const Identifier& id)
{
    Add(id);
}

void Name::Add(std::string piece)
{
    if (Identifier::IsValidName(piece))
    {
        namePieces.push_back(piece);
    }
    else
    {
        piece = "'" + piece + "'";
        namePieces.push_back(piece);
    }
}

void Name::Add(const Identifier& id)
{
    // No need to check for validity, the identifier has already checked it
    namePieces.push_back(id.GetString());
}

void Name::Add(const char* piece)
{
    Add(std::string(piece));
}

std::string Name::GetString() const
{
    std::ostringstream ss;
    ss << (*this);
    return ss.str();
}

std::ostream& operator<<(std::ostream& out, const Identifier& id)
{
    out << id.name;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Name& name)
{
    // Concatenate all the pieces with '.'
    bool first = true;

    for (std::string piece : name.namePieces)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            out << '.';
        }
        out << piece;
    }

    return out;
}



