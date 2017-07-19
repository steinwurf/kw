// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include "parameter.hpp"
#include "argument.hpp"

#include <type_traits>
#include <cassert>
#include <iostream> // @todo remove

namespace kw
{

namespace detail
{
    /// Small helper for finding the arguments matching a parameter in
    /// the variadic template pack.
    template<class Value>
    struct find_parameter
    {

        /// Overload for get when no more arguments are available.
        static const argument<Value>* get(const parameter<Value>& param)
        {
            (void) param;
            return nullptr;
        }

        /// Overload of the get(...) function where the template parameter
        /// SomeValue != Value. This means that an argument does not
        /// have the value type we are looking for. So we do not need to
        /// check the key, we just check the next argument.
        template<class SomeValue, class... Arguments>
        static const argument<Value>* get(
            const parameter<Value>& param,
            const argument<SomeValue>& arg,
            const Arguments&... args)
        {
            (void) arg;
            return get(param, args...);
        }

        /// Overload of the get(...) function where the argument has the
        /// rigth value type so we need to check the key. If the key
        /// matches we return the argument.
        template<class... Arguments>
        static const argument<Value>* get(
            const parameter<Value>& param,
            const argument<Value>& arg,
            const Arguments&... args)
        {

            if (&param == std::get<0>(arg))
            {
                return std::addressof(arg);
            }

            return get(param, args...);
        }
    };

}

/// Find and return the value of the parameter. If the parameter cannot
/// be found we assert!
///
template<class Value, class... Arguments>
Value get(
    const parameter<Value>& param,
    const Arguments&... args)
{
    const argument<Value>* ptr =
        detail::find_parameter<Value>::get(param, args...);

    assert(ptr != nullptr && "An argument for a required parameter "
        "was not passed.");

    return std::get<1>(*ptr);
}

/// Try to find an argument matching the parameter. If an argument is
/// found we copy it to the passed reference and return true. Otherwise we
/// just return false.
///
template<class Value, class... Arguments>
bool get(
    const parameter<Value>& param,
    Value& value,
    const Arguments&... args)
{
    const argument<Value>* ptr =
        detail::find_parameter<Value>::get(param, args...);

    if (ptr)
    {
        value = std::get<1>(*ptr);
        return true;
    }
    else
    {
        return false;
    }
}

}
