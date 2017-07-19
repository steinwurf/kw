// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/parameter.hpp>

#include <string>
#include <cstdint>
#include <tuple>

#include <gtest/gtest.h>

#include "test_parameters.hpp"

namespace
{

const kw::parameter<uint32_t> alpha;
const kw::parameter<bool> bravo;
const kw::parameter<std::string> charlie;
}

TEST(test_arg, convert)
{
}
