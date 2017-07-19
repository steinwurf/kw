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

Optional arguments
------------------

Let's create a 2D point class::

    const kw::parameter<uint32_t> x;
    const kw::parameter<uint32_t> y;
    const kw::parameter<std::string> name;

    class point
    {
    public:

        template<class... Args>
        point(const Args&... args)
        {
            // Extract optional values
            kw::get(name, m_name, args...);
            kw::get(x, m_x, args...);
            kw::get(y, m_y, args...);
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

        std::string m_name = "point";
        uint32_t m_x = 0;
        uint32_t m_y = 0;
    };

We can now create a point by specifying all the values::

    point p = point(x=10, y=20, name="cool point");

    std::string out = p.to_string();
    assert(out == "m_name=cool point, m_x=10, m_y=20");

We can also create a point while only specifying a subset of the values,
e.g. the name::

    point p = point(y=20);

    std::string out = p.to_string();
    assert(out == "m_name=point, m_x=0, m_y=20");

And we can create a box by specifying none of the values::

    point p = point();

    std::string out = p.to_string();
    assert(out == "m_name=point, m_x=0, m_y=0");

Checking whether an optional argument was specified
----------------------------------------------------

If needed it is also possible to check whether an argument was specified.
The optional version of the get function returns a bool indicating whether
the argument was found::

    const kw::parameter<double> temperature;

    class thermometer
    {
    public:

        template<class... Args>
        thermometer(const Args&... args)
        {
            bool found = kw::get(temperature, m_temperature, args...);
            assert(found);
        }

        double temp() const
        {
            return m_temperature;
        }

    private:

        double m_temperature = 0;
    };

In this case the code will assert if ``temperature`` is not passed as an
argument::

    thermometer t = thermometer(temperature=10.0);
    assert(t.temp() == 10.0);

Non-optional arguments
----------------------

If certain arguments are required a ...


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
