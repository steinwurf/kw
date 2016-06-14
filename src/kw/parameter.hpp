// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <type_traits>

namespace kw
{
    template <class Value>
    struct parameter
    {
        const void* key;
        Value value;
    };
}
