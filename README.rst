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
multiple definitions error. One way to fix this is to define them in a ``cpp``
file.

Let's create a 2D box class::

  #include <kw/arg.hpp>

  kw::arg<uint32_t> x, y, width, height;
  kw::arg<std::string> name;

  class box
  {

  public:

    template<class... Args>
    void create_box(Args&... args)
    {
      // setup default values
      uint32_t x_arg = 0;
      uint32_t y_arg = 0;
      uint32_t width_arg = 10;
      uint32_t height_arg = 10;
      std::string name_arg = "box";

      // extract values
      kw::get(x, x_arg, args...);
      kw::get(y, y_arg, args...);
      kw::get(width, width_arg, args...);
      kw::get(height, height_arg, args...);
      kw::get(name, name_arg, args...);

      // use parameters to create box...
    }
  }

We can now create a box by specifying all the values::

    auto my_box = box(x=10, y=20, width=44, height=87, name="cool box");

And we can create a box by specifying none of the values::

    auto my_other_box = box();

Finally we can also create a box while only specifying the name::

    auto my_named_box = box(name="almost a standard box");

License
=======
The kw library is released under the BSD license see the LICENSE.rst file.

Credit
======
When designing kw we used the following project as a starting point:
`CaptainCrowbar/kwargs <https://github.com/CaptainCrowbar/kwargs>`_.
