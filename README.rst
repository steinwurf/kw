==
kw
==

kw is a tiny library which enables the use of keyword arguments in C++.

.. contents:: Table of Contents:
   :local:

Usage
=====

The benefits provided by the use of keyword arguments are plentiful, you can
find a subset of these `here <http://en.wikipedia.org/wiki/Named_parameter>`_.

To use kw you must define each of you parameter names as global objects.
If you define these in a header file, chances are that you will get a
multiple definitions error. To avoid this declare the parameters as const
to give them internal linkage. Or alternatively define them in a ``cpp``
file.

Let's create a 2D box class::

    #include <kw/arg.hpp>

    #include <string>
    #include <cstdint>
    #include <iostream>

    kw::arg<uint32_t> x, y, width, height;
    kw::arg<std::string> name;

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

We can now create a box by specifying all the values::

    auto my_box = box(x=10, y=20, width=44, height=87, name="cool box");

And we can create a box by specifying none of the values::

    auto my_other_box = box();

Finally we can also create a box while only specifying a subset of the values,
e.g. the name::

    auto my_named_box = box(name="almost a standard box");

You can find this example in the examples folder.

Notes
=====
We need the parameters to have the same address:
https://stackoverflow.com/a/27349508

Terminology
===========

Argument and parameter
----------------------

Taken from the following stackoverflow answer:
https://stackoverflow.com/a/156787

So basically in the following example::

    // a and b are the two parameters
    uint32_t sum(uint32_t a, uint32_t b)
    {
    ...
    }

    int main()
    {
        // Here 4 is the argument for parameter a and 5 is the argument
        // for the parameter b.
        uint32_t v = sum(4,5);
    }


License
=======
The kw library is released under the BSD license see the LICENSE.rst file.

Credit
======
When designing kw we used the following project as a starting point:
`CaptainCrowbar/kwargs <https://github.com/CaptainCrowbar/kwargs>`_. This
was later removed. But the code still exist in a different repository:
https://goo.gl/nA1NqY

Related work
============
Later on we also discovered other related works:
- https://github.com/cheshirekow/kwargs
