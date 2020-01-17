This kata was developed on a Linux environment running the Mint 19 Cinnamon OS, version 3.8.8, and the g++ compiler, version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1)

The environment required to build this solution and run these tests includes a Linux environment with g++ version 7.4.0 and the ability to run makefiles.

The only dependancy required is the Catch single header library, which is included in the lib/ folder. This library will be compiled by the makefile, no extra action is needed. The makefile may take a moment to compile when ran for the first time due to compiling this library.

To build and run all tests, simply type "make test"

After running, object files and executable can be removed using "make clean"
