// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/arg.hpp>

#include <string>
#include <cstdint>
#include <tuple>

#include <gtest/gtest.h>

namespace
{

    const kw::arg<uint32_t> alpha;
    const kw::arg<bool> bravo;
    const kw::arg<std::string> charlie;

    template<class... Args>
    std::tuple<uint32_t, bool, std::string> test_function(const Args&... args)
    {
        // defaults
        uint32_t a = 0;
        bool b = false;
        std::string c = "";

        kw::get(alpha, a, args...);
        kw::get(bravo, b, args...);
        kw::get(charlie, c, args...);
        auto result = std::make_tuple(a, b, c);
        return result;
    }
}

TEST(test_arg, no_arguments)
{
    auto result = test_function();

    uint32_t a;
    bool b;
    std::string c;

    std::tie(a, b, c) = result;

    EXPECT_EQ(0U, a);
    EXPECT_FALSE(b);
    EXPECT_EQ("", c);
}

TEST(test_arg, all_arguments)
{
    auto result = test_function(alpha=42U, bravo, charlie="charles");

    uint32_t a;
    bool b;
    std::string c;

    std::tie(a, b, c) = result;

    EXPECT_EQ(42U, a);
    EXPECT_EQ(true, b);
    EXPECT_EQ("charles", c);
}

TEST(test_arg, single_argument)
{
    // First argument specified
    {
        auto result = test_function(alpha=42U);

        uint32_t a;
        bool b;
        std::string c;

        std::tie(a, b, c) = result;

        EXPECT_EQ(42U, a);
        EXPECT_FALSE(b);
        EXPECT_EQ("", c);
    }
    // Second argument specified
    {
        auto result = test_function(bravo);

        uint32_t a;
        bool b;
        std::string c;

        std::tie(a, b, c) = result;

        EXPECT_EQ(0U, a);
        EXPECT_EQ(true, b);
        EXPECT_EQ("", c);
    }
    // Third argument specified
    {
        auto result = test_function(charlie="charles");

        uint32_t a;
        bool b;
        std::string c;

        std::tie(a, b, c) = result;

        EXPECT_EQ(0U, a);
        EXPECT_FALSE(b);
        EXPECT_EQ("charles", c);
    }
}
