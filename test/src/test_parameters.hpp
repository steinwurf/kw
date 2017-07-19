// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/parameter.hpp>

namespace test
{
    // When defining parameters in headers we need to make sure that they
    // have internal linkage such that we do not get multiple definition
    // errors.
    //
    // One way to ensure internal linkage is to declare the variable const
    // https://stackoverflow.com/a/6173889

    const kw::parameter<uint32_t> height;
    const kw::parameter<uint32_t> weight;

}
