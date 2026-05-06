/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** FactoryTemplate
*/

#pragma once

#include <functional>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <utility>

namespace designPattern {
template <typename BaseClass, typename ConcreteClass, typename... Args>
concept HasCreateMethod = requires(Args... args) {
    {
        ConcreteClass::create(std::forward<Args>(args)...)
    } -> std::same_as<std::unique_ptr<BaseClass>>;
};

template <typename BaseClass, typename KeyType, typename... Args>
class FactoryTemplate {
public:
    using CreatorCallable = std::function<std::unique_ptr<BaseClass>(Args...)>;
    using CreatorMap      = std::unordered_map<KeyType,
        std::function<std::unique_ptr<BaseClass>(Args...)>>;

    FactoryTemplate() = default;

    ~FactoryTemplate() = default;

    FactoryTemplate(const FactoryTemplate &) = delete;

    FactoryTemplate(const FactoryTemplate &&) = delete;

    FactoryTemplate &operator=(const FactoryTemplate &) = delete;

    FactoryTemplate &operator=(const FactoryTemplate &&) = delete;

    template <typename ConcreteClass>
        requires HasCreateMethod<BaseClass, ConcreteClass, Args...>
    void registerCreator(KeyType key)
    {
        _creators[key] = &ConcreteClass::create;
    }

    void unregisterCreator(KeyType key)
    {
        _creators.erase(key);
    }

    std::unique_ptr<BaseClass> create(const KeyType &key, Args... args)
    {
        const auto itt = _creators.find(key);

        if (itt != _creators.end())
            return (*itt).second(std::forward<Args>(args)...);

        std::stringstream sstream;
        sstream << "No creator found for key: " << key;
        throw std::runtime_error(sstream.str());
    }

private:
    CreatorMap _creators{};
};
} // namespace designPattern
