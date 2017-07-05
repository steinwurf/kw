// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/parameter.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_parameter, test)
{
    kw::parameter<uint32_t> param;
    param = {(const void*)0xdeadbeef, 42U};

    EXPECT_EQ(42U, std::get<1>(param));
}
