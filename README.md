# cpp-aio
cpp-aio is a collection of reusable components for asynchronous IO in C++. It differentiates itself from other libraries, especially the Boost ASIO library, by not using a complicated execution model. cpp-aio insttead provides 
extensible templates for a simple trigger-based system that can be easily specialized to the poll/select model for any given system. It also provides non-portable C++ iostream implementations of network sockets for unix-like 
systems.

## Including cpp-aio into a project.
The components of cpp-aio can be found under ``src/io/``. The easiest way to use any of these components is to include ``io.hpp`` into the project, then compile and link the code provided here.

