#pragma once

#include <iostream>

class Stream
{
public:
    Stream(std::ostream& output);

    void IncrementIndent() { indentLevel++; }
    void DecrementIndent() { indentLevel--; }

    template <class T>
    Stream& operator<<(const T& val)
    {
        if (needIndent)
        {
            PrintIndent();
            needIndent = false;
        }

        output << val;
        return *this;
    }

    using manipulator_func = std::ostream& (*)(std::ostream&);

    Stream& operator<<(manipulator_func val)
    {
        output << val;
        needIndent = true;
    }

private:
    void PrintIndent();

    std::ostream& output;
    int indentLevel = 0;
    bool needIndent = true;
};


