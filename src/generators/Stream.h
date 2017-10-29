#pragma once

#include <iostream>
#include <type_traits>

#include "Generator.h"

class Stream
{
public:
    Stream(std::ostream& output);

    void IncrementIndent() { indentLevel++; }
    void DecrementIndent() { indentLevel--; }

    template <class T, class = typename std::enable_if<!std::is_base_of<Generator,T>::value>::type>
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

    Stream& operator<<(const Generator& generator)
    {
        if (needIndent)
        {
            PrintIndent();
            needIndent = false;
        }

        generator.Generate(*this);
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


