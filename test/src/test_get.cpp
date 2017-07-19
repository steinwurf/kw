// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/get.hpp>

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

TEST(test_arg, no_arguments)
{
    uint32_t found_alpha = 0;
    bool found = kw::get(alpha, found_alpha, bravo=true, charlie="ch");
    EXPECT_FALSE(found);
}

TEST(test_arg, all_arguments)
{
    uint32_t a;
    bool b;
    std::string c;

    EXPECT_TRUE(kw::get(alpha, a, alpha=42U, bravo=true, charlie="charles"));
    EXPECT_TRUE(kw::get(bravo, b, alpha=42U, bravo=true, charlie="charles"));
    EXPECT_TRUE(kw::get(charlie, c, alpha=42U, bravo=true, charlie="charles"));

    EXPECT_EQ(42U, a);
    EXPECT_EQ(true, b);
    EXPECT_EQ("charles", c);

    EXPECT_EQ(42U, kw::get(alpha, alpha=42U, bravo=true, charlie="charles"));
    EXPECT_EQ(true, b);
    EXPECT_EQ("charles", c);
}

TEST(test_arg, get)
{
    const kw::parameter<uint32_t> alpha;

    uint32_t value = kw::get(alpha, alpha=39U);
    EXPECT_EQ(value, 39U);
}

TEST(test_arg, get_const)
{
    const kw::parameter<const uint32_t> alpha;

    uint32_t value = kw::get(alpha, alpha=39U);
    EXPECT_EQ(value, 39U);
}

TEST(test_arg, get_pointer)
{
    const kw::parameter<uint32_t*> alpha;

    uint32_t* value = kw::get(alpha, alpha=(uint32_t*)0xdeadbeef);
    EXPECT_EQ(value, (uint32_t*)0xdeadbeef);
}

TEST(test_arg, get_const_pointer)
{
    const kw::parameter<const uint32_t*> alpha;

    const uint32_t* value = kw::get(alpha, alpha=(const uint32_t*)0xdeadbeef);
    EXPECT_EQ(value, (const uint32_t*)0xdeadbeef);
}

TEST(test_arg, get_reference)
{
    const kw::parameter<uint32_t&> alpha;

    uint32_t number = 5;
    uint32_t& value = kw::get(alpha, alpha=number);
    EXPECT_EQ(value, number);
}

TEST(test_arg, get_const_reference)
{
    const kw::parameter<const uint32_t&> alpha;

    uint32_t number = 5;
    const uint32_t& value = kw::get(alpha, alpha=number);
    EXPECT_EQ(value, number);
}
