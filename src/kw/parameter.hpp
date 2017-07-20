// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <utility>
#include <type_traits>

#include "argument.hpp"

namespace kw
{
template<class Value>
struct parameter
{
    parameter()
    { }

    template<class Arg>
    argument<Value> operator=(Arg&& arg) const
    {
        return argument<Value>(this, std::forward<Arg>(arg));
    }
};

/// The following was added to support const reference parameters.
/// There is a problem with const references which can cause dangling
/// references.
/// The test in test_get.cpp called TEST(test_arg, get_const_reference)
/// would expose this problem if not handled. So what we do here is
/// that if the Value is a const reference we return it by value.
///
/// Read more about the problem here:
/// https://stackoverflow.com/a/667415

template<class Value>
struct parameter<const Value&>
{
    parameter()
    { }

    template<class Arg>
    argument<const Value&> operator=(Arg&& arg) const
    {
        // We need to use decltype(arg) to see if arg is a r-value
        static_assert(!std::is_rvalue_reference<decltype(arg)>::value,
                      "No r-value can be passed to const & parameter without "
                      "creating dangling references.");
        return argument<const Value&>(this, std::forward<Arg>(arg));
    }
};

}
