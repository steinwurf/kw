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
        parameter<Value> operator=(const Arg& argument) const
        {
            return {this, argument};
        }
    };

    template<class Key, class Value, class Parameter, class... Args>
    void get(
        const arg<Key>& key,
        Value& value,
        const parameter<Parameter>& param,
        const Args&... args)
    {
        if (&key == param.key)
            copy<Parameter, Value>()(param.value, value);
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
}
