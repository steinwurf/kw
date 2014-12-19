// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/steinwurf_version.hpp>
#include <gtest/gtest.h>

TEST(TestVersion, not_empty)
{
    EXPECT_FALSE(kw::steinwurf_version().empty());
}
