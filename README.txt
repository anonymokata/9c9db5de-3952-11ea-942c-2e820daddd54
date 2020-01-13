The environment required to build this solution and run these tests includes any g++ version with C++11 support and the ability to run makefiles.

The only dependancy required is the Catch single header library, which is included in the lib/ folder. This library will be compiled by the makefile, no extra action is needed. The makefile may take a moment to compile when ran for the first time due to compiling this library.

To build and run all tests, simply type "make test"

After running, object files and executable can be removed using "make clean"
