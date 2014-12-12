// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/copy.hpp>
#include <gtest/gtest.h>

TEST(test_copy, test)
{
    {
        uint32_t source = 4U;
        uint32_t destination = 0U;

        kw::copy<uint32_t, uint32_t>()(source, destination);

        EXPECT_EQ(source, destination);
    }
    {
        uint32_t source = 4U;
        uint8_t destination = 0U;

        kw::copy<uint32_t, uint8_t>()(source, destination);

        EXPECT_EQ(4U, destination);
    }
    {
        uint32_t source = 4U;
        std::string destination = "";

        kw::copy<uint32_t, std::string>()(source, destination);

        EXPECT_EQ("", destination);
    }
}