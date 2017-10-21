#pragma once

#include <unordered_map>
#include <memory>
#include <functional>
#include <stdexcept>

class NotFoundException : std::runtime_error
{
public:
    NotFoundException(std::string message) : std::runtime_error(message) {}
};


template <class TKey, class TVal>
class UniqueDict
{
public:
    using ValPtr = std::unique_ptr<TVal>;
    using const_iterator = std::unordered_map<TKey, ValPtr>::const_iterator;

    UniqueDict() {}

    template <class... Args>
    TVal* GetOrCreateValue(const TKey& key, Args&&... args)
    {
        auto iter = map.find(key);
        if (iter != map.end())
            return iter->second.get();

        ValPtr newVal = std::make_unique<TVal>(std::forward<Args>(args)...);

        TVal* weak = newVal.get();
        map.emplace(key, std::move(newVal));
        return weak;
    }

    TVal* GetOrCreateValueWithFactory(const TKey& key, std::function<ValPtr()> factory)
    {
        auto iter = map.find(key);
        if (iter != map.end())
            return iter->second.get();

        ValPtr newVal = factory();

        TVal* weak = newVal.get();
        map.emplace(key, std::move(newVal));
        return weak;
    }


    TVal* GetValue(const TKey& key)
    {
        auto iter = map.find(key);
        if (iter != map.end())
            return iter->second.get();

        throw NotFoundException("Key was not found");
    }

    bool Contains(const TKey& key) const
    {
        return map.find(key) != map.end();
    }

    const_iterator begin() const { return map.cbegin(); }
    const_iterator end() const { return map.cend(); }

private:
    std::unordered_map<TKey, ValPtr> map;
};

