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

Using keyword parameters
------------------------

There are two functions available when utilizing keyword parameters in
your application. A short description and signature is show here for
reference. Following this section you can find a few examples of how to use
both.

Using optional arguments::

    // Define some parameters
    const kw::parameter<uint32_t> x_param;
    const kw::parameter<uint32_t> y_param;

    // Define a value to capture the argument
    uint32_t x_value;

    // Found will be true of false depending on whether x_param was passed
    bool found = kw::get(x_param, x_value, x_param=10, y_param=10);
    //     +                +        +         +          +
    //     |                |        |         |          |
    //     |                |        |         v          v
    //     |                |        |         Any number of parameter
    //     |                |        |         arguments
    //     |                |        |
    //     |                |        +----> Where to store the found value
    //     |                |
    //     |                +----> Parameter we are looking for
    //     |
    //     +----> Boolean indicating whether argument was found


Using non-optional arguments::

    // Define some parameters
    const kw::parameter<uint32_t> x_param;
    const kw::parameter<uint32_t> y_param;

    // Define a value to capture the argument (must be found)
    uint32_t x_value = kw::get(x_param, x_param=10, y_param=10);
    //         +                +            +          +
    //         |                |            |          |
    //         |                |            v          v
    //         |                |            Any number of parameter
    //         |                |            arguments
    //         |                |
    //         |                +----> Parameter we are looking for
    //         |
    //         +----> Where to store the found value


Larger example of optional arguments
------------------------------------

Let's create a 2D point class::

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
            kw::get(name, m_name, args...);
            kw::get(x, m_x, args...);
            kw::get(y, m_y, args...);
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
    };

We can now create a point by specifying all the values::

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

We can also create a point while only specifying a subset of the values,
e.g. the name::

    uint32_t counter = 0U;
    point p = point(y=20, count=counter);

    std::string out = p.to_string();
    assert(out == "m_name=point, m_x=0, m_y=20");

And we can create a point specifying only the non-optional of the values::

    uint32_t counter = 0U;
    point p = point(count=counter);

    std::string out = p.to_string();
    assert(out == "m_name=point, m_x=0, m_y=0");

Checking optional arguments
---------------------------

Lets look at a simple example where we check whether an optional argument
was found - and based on the result perform some action::

    const kw::parameter<std::string> configuration;

    inline std::string load_from_file()
    {
        // Just to illustrate the possibility - imagine that we now loaded
        // a configuration from a file :)
        //
        // Also probably not a good idea to do this kind of stuff in a
        // constructor - but anyways for the sake of the example...
        return "I just loaded this - promise :)";
    }

    struct server
    {
        template<class... Args>
        server(const Args&... args)
        {
            // Extract optional values
            if(!kw::get(configuration, m_configuration, args...))
            {
                m_configuration = load_from_file();
            }
        }

        std::string m_configuration;
    };

If the optional argument ``configuration`` is not found the
``load_from_file(...)`` function is invoked::

    server s = server();

    assert(s.m_configuration == "I just loaded this - promise :)");

If the optional argument is specified it is used instead::

    server s = server(configuration="Please use this configuration");

    assert(s.m_configuration == "Please use this configuration");



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
