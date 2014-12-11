// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <type_traits>

namespace kw
{
    template<
        class Source,
        class Destination,
        bool = std::is_convertible<Source, Destination>::value>
    struct copy {
        void operator()(const Source& source, Destination& destination) const
        {
            destination = source;
        }
    };
    template<
        class Source,
        class Destination>
    struct copy<Source, Destination, false> {
        void operator()(const Source& source, Destination& destination) const
        {
            (void) source;
            (void) destination;
        }
    };
}