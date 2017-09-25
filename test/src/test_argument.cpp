// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/argument.hpp>

#include <cstdint>

#include <gtest/gtest.h>

TEST(test_argument, test)
{
    kw::argument<uint32_t> param((const void*)0xdeadbeef, 42U);

    EXPECT_EQ((const void*)0xdeadbeef, std::get<0>(param));
    EXPECT_EQ(42U, std::get<1>(param));
}
