#pragma once

#include <sstream>
#include <memory>

namespace
{
    void FormatStringHelper(std::stringstream& ss) { }

    template <class Arg, class... Args>
    void FormatStringHelper(std::stringstream& ss, const Arg& arg1, const Args&... args)
    {
        ss << arg1;
        FormatStringHelper(ss, args...);
    }

}

template <class... Args>
std::string Format(const Args&... args)
{
    std::stringstream ss;
    FormatStringHelper(ss, args...);
    return ss.str();
}

namespace std
{
    template <class T, class... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
