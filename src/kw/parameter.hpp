// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <tuple>

namespace kw
{
template<class Value>
using parameter = std::tuple<const void*, Value>;
}
