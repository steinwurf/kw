// Copyright Steinwurf ApS 2014.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <kw/arg.hpp>

#include <string>
#include <cstdint>
#include <iostream>

#include <prettyprint.hpp>

namespace
{
kw::arg<uint32_t> x;
kw::arg<uint32_t> y;
kw::arg<uint32_t> width;
kw::arg<uint32_t> height;
kw::arg<std::string> name;
kw::arg<uint8_t&> counter;

class box
{

public:

    template<class... Args>
    box(const Args&... args)
    {
        // extract values
        kw::get(name, m_name, args...);
        kw::get(x, m_x, args...);
        kw::get(y, m_y, args...);
        kw::get(width, m_width, args...);
        kw::get(height, m_height, args...);

        auto m_f = kw::get_r(x, args...);
        std::cout << "tuple=" << m_f << std::endl;
    }

    void print()
    {
        std::cout << "name:   " << m_name << std::endl;
        std::cout << "x:      " << m_x << std::endl;
        std::cout << "y:      " << m_y << std::endl;
        std::cout << "width:  " << m_width << std::endl;
        std::cout << "height: " << m_height << std::endl;
    }

private:

    std::string m_name = "box";
    uint32_t m_x = 0;
    uint32_t m_y = 0;
    uint32_t m_width = 10;
    uint32_t m_height = 10;

};


template<class... Args>
void tests(const Args&... args)
{
    auto d = kw::get_r(x, args...);
}

}

int main()
{
    uint8_t count = 0;

    tests(count);

    // We can now create a box by specifying all the values
    //auto my_box = box(x=10U, y=20U, width=44U, height=87U, name="cool box", counter=std::ref(count));
    // std::cout << "printing my_box:" << std::endl;
    // my_box.print();
    // std::cout << std::endl;
    //
    // // And we can create a box by specifying none of the values
    // auto my_other_box = box();
    // std::cout << "printing my_other_box:" << std::endl;
    // my_other_box.print();
    // std::cout << std::endl;
    //
    // // Finally we can also create a box while only specifying the name
    // auto my_named_box = box(name="almost a standard box");
    // std::cout << "printing my_named_box:" << std::endl;
    // my_named_box.print();



}
