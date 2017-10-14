#pragma once

#include <typeinfo>
#include <typeindex>
#include <unordered_set>

using TypeSet = std::unordered_set<std::type_index>;

namespace
{
    template <class... Types>
    struct TypeSetHelper;

    template <class Type, class... Types>
    struct TypeSetHelper<Type, Types...>
    {
    public:
        static void Create(TypeSet& typeset)
        {
            typeset.insert(std::type_index(typeid(Type)));
            TypeSetHelper<Types...>::Create(typeset);
        }
    };

    template<>
    struct TypeSetHelper<>
    {
    public:
        static void Create(TypeSet& typeset) {}
    };
}

template <class... Types>
std::unordered_set<std::type_index> CreateTypeSet()
{
    TypeSet typeset;
    TypeSetHelper<Types...>::Create(typeset);
    return typeset;
}
