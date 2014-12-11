// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/kwarg.hpp>

#include <string>
#include <cstdint>
#include <tuple>

#include <gtest/gtest.h>

namespace
{

    const kw::kwarg<uint32_t> alpha;
    const kw::kwarg<bool> bravo;
    const kw::kwarg<std::string> charlie;

    template<class... Args>
    std::tuple<uint32_t, bool, std::string> test_function(const Args&... args)
    {

        uint32_t a = 0;
        bool b = false;
        std::string c = "";

        kw::kwget(alpha, a, args...);
        kw::kwget(bravo, b, args...);
        kw::kwget(charlie, c, args...);
        auto result = std::make_tuple(a, b, c);
        return result;
    }
}

TEST(test_kwarg, no_arguments)
{
    auto result = test_function();

    uint32_t a;
    bool b;
    std::string c;

    std::tie (a, b, c) = result;

    EXPECT_EQ(0, a);
    EXPECT_FALSE(b);
    EXPECT_EQ("", c);
}

TEST(test_kwarg, all_arguments)
{
    auto result = test_function(alpha=42, bravo, charlie="yes");

    uint32_t a;
    bool b;
    std::string c;

    std::tie (a, b, c) = result;

    EXPECT_EQ(42, a);
    EXPECT_TRUE(b);
    EXPECT_EQ("yes", c);
}
