// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/get.hpp>

#include <string>
#include <cstdint>
#include <iostream>

namespace
{
const kw::parameter<uint32_t&> counter;
const kw::parameter<uint32_t> x;
const kw::parameter<uint32_t> y;
const kw::parameter<uint32_t> width;
const kw::parameter<uint32_t> height;
const kw::parameter<std::string> name;

class box
{
public:

    // There are two ways to extract arguments, one where the argument is
    // non optional and is returned by the kw::get(...) function and one
    // where the argument is optional is stored in the passed value if
    // found.
    //
    //  Below we use both variants. First in the initializer list we use
    //  the non-optional version to extract the reference to the counter.
    //
    //   Sencondly we use the optional version to extract the memeber
    //   variables.
    template<class... Args>
    box(const Args&... args) :
        m_counter(kw::get(counter, args...))
    {
        // extract values
        kw::get(name, m_name, args...);
        kw::get(x, m_x, args...);
        kw::get(y, m_y, args...);
        kw::get(width, m_width, args...);
        kw::get(height, m_height, args...);
    }

    void print()
    {
        std::cout << "counter:   " << m_counter << std::endl;
        std::cout << "name:   " << m_name << std::endl;
        std::cout << "x:      " << m_x << std::endl;
        std::cout << "y:      " << m_y << std::endl;
        std::cout << "width:  " << m_width << std::endl;
        std::cout << "height: " << m_height << std::endl;
    }

private:

    uint32_t& m_counter;
    std::string m_name = "box";
    uint32_t m_x = 0;
    uint32_t m_y = 0;
    uint32_t m_width = 10;
    uint32_t m_height = 10;

};
}

int main()
{
    uint32_t count = 0;

    //We can now create a box by specifying all the values
    box my_box = box(x=10U, y=20U, width=44U, height=87U, name="cool box",
                     counter=count);

    std::cout << "printing my_box:" << std::endl;
    my_box.print();
    std::cout << std::endl;

    // And we can create a box by specifying none of the values
    box my_other_box = box(counter=count);
    std::cout << "printing my_other_box:" << std::endl;
    my_other_box.print();
    std::cout << std::endl;

    // Finally we can also create a box while only specifying the name
    auto my_named_box = box(counter=count, name="almost a standard box");
    std::cout << "printing my_named_box:" << std::endl;
    my_named_box.print();
}
