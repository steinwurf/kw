// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include "parameter.hpp"
#include "copy.hpp"

#include <type_traits>

namespace kw
{
template<class Value>
struct arg
{
    arg()
    { }

    template<class Arg>
    parameter<Value> operator=(Arg&& argument) const
    {
        return {this, std::forward<Arg>(argument)};
    }
};

template<class Key, class Value, class Parameter, class... Args>
void get(
    const arg<Key>& key,
    Value& value,
    const parameter<Parameter>& param,
    const Args&... args)
{
    if (&key == std::get<0>(param))
        copy<Parameter, Value>()(std::get<1>(param), value);
    get(key, value, args...);
}

template<class Key, class Value, class... Args>
void get(
    const arg<Key>& key,
    Value& value,
    const arg<bool>& param,
    const Args&... args)
{
    get(key, value, param = true, args...);
}

template <class Key, class Value>
void get(const arg<Key>&, Value&)
{ }


/// This is the kind of functionality I need:
/// https://stackoverflow.com/q/36747123

template<class Value, class... Parameters>
Value get_r(
    const arg<Value>& key,
    const Parameters&... parameters)
{


    auto convertible = std::tuple_cat(
        std::get<std::is_convertible<decltype(std::get<1>(parameters)), Value>::value ? 0 : 1>(
            std::make_tuple(std::tuple<>(), parameters))...);

    //
    // auto convertible = std::tuple_cat(
    //     std::get<std::is_convertible<Value, std::get<1>(parameters)>::value ? 0 : 1>(
    //         std::make_tuple(parame, std::tuple<>()))...);

    return Value(0);
}


}
