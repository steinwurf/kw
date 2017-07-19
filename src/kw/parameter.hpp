// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <utility>

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
}
