====================================
  `httpxx` --- HTTP Parser for C++
====================================
:authors:
   André Caron
:contact: andre.l.caron@gmail.com
:version:
   0.1
:date: 2011-07-18

Description
===========

This library is a simple C++ wrapper for the C library ``http-parser`` [#]_
(This code was derived from the HTTP parser code in NGINX_).  ``http-parser`` is
a simple HTTP streaming parser (for those of you familiar with XML, it works
much like a SAX parser).  It knows nothing of sockets or streams.  You feed it
data and it invokes registered callbacks to notify of available data.  Because
``http-parser`` operates at the very lowest level, it does not buffer data or
allocate memory dynamically.  This library attempts to make that library easily
usable by C++ programs by interpreting those callbacks and buffering data where
needed.

.. [#] https://github.com/ry/http-parser.

.. _NGINX: http://nginx.net/

Documentation
=============

The API for defined classes is documented using Doxygen [#]_.  You will need to
run Doxygen from the project source folder to generate the output HTML.

.. [#] http://www.stack.nl/~dimitri/doxygen/

Compiled HTML documentation for official releases is available online.  Check
the `project page`_.

.. _`project page`: http://andrelouiscaron.github.com/httpxx/

Fetching the code
=================

This project does not distribute the code to ``http-parser`` directly.  To fetch
the entire source code, make sure you fetch submodules [#]_ too:

::

   $ git clone ...
   $ cd httpxx
   $ git submodule init
   $ git submodule update

.. [#] http://book.git-scm.com/5_submodules.html

Portability
===========

``http-parser`` itself has no dependencies and compiles with C++ compilers.
``httpcxx`` uses only standard library facilities (namely ``std::string`` and
``std::map``) and introduces no additional dependencies.

The code should compile as is under a standard-compliant C++03 implementation.

Memory allocation policy
========================

A good memory allocation policy is important in server programs, which typically
run for a long time and suffer from memory fragmentation.  ``httpcxx`` does its
best to avoid repeated allocation, but it needs a little help on your part.

``http::Request`` and ``http::Response`` parser object allocate memory as
required because they buffer different parts of the incoming HTTP
request/response in ``std::string`` instances.  However, they are implemented
carefully as to use the growing property of ``std::string`` [#]_ to their
advantage.  In particular, you may re-use ``http::Request`` and
``http::Response`` parser objects for parsing multiple request/response objects
using their ``.clear()`` method.  This method marks all header lengths as 0 but
keeps the instances as well as the map.  All this ensures that parsers avoid
repeated memory allocation.

.. [#] ``std::string`` instances keep the allocated memory buffer even when you
   resize them such that their length decreases.  In particular,
   ``std::string::clear()`` marks the string length as 0 but keeps the allocated
   buffer.

Samples / demos
===============

Check out the sample programs in the ``demo/`` subfolder.

.. _`http-parser`: https://github.com/ry/http-parser
