// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <gtest/gtest.h>

#include <kw/get.hpp>

#include <string>
#include <sstream>
#include <cstdint>
#include <iostream>

namespace
{
const kw::parameter<uint32_t&> count;
const kw::parameter<uint32_t> x;
const kw::parameter<uint32_t> y;
const kw::parameter<std::string> name;

class point
{
public:

    template<class... Args>
    point(const Args&... args) :
        m_count(kw::get(count, args...))
    {
        // Increment the count
        ++m_count;

        // Extract optional values
        m_name_default = kw::get(name, m_name, args...);
        m_x_default = kw::get(x, m_x, args...);
        m_y_default = kw::get(y, m_y, args...);
    }

    ~point()
    {
        --m_count;
    }

    std::string to_string()
    {
        std::stringstream ss;
        ss << "m_name=" << m_name << ", ";
        ss << "m_x=" << m_x << ", ";
        ss << "m_y=" << m_y;
        return ss.str();
    }

private:

    uint32_t& m_count;
    std::string m_name = "point";
    uint32_t m_x = 0;
    uint32_t m_y = 0;
    bool m_name_default = false;
    bool m_x_default = false;
    bool m_y_default = false;
};

}

TEST(test_readme, specify_all)
{
    uint32_t counter = 0U;
    {
        // Create a scope to see the counter update
        point p = point(count=counter, x=10U, y=20U, name="cool point");
        assert(counter == 1U);

        std::string out = p.to_string();
        assert(out == "m_name=cool point, m_x=10, m_y=20");
    }

    // The counter is now adjusted as the point goes out of scope
    assert(counter == 0U);
}

TEST(test_readme, specify_some)
{
    uint32_t counter = 0U;
    point p = point(y=20, count=counter);

    std::string out = p.to_string();
    assert(out == "m_name=point, m_x=0, m_y=20");
}

TEST(test_readme, specify_none)
{
    uint32_t counter = 0U;
    point p = point(count=counter);

    std::string out = p.to_string();
    assert(out == "m_name=point, m_x=0, m_y=0");
}
