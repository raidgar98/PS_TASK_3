# Task for System Programming

## Requirements:

By requirements i mean downloaded, with setted preoper paths, so cmake can find it

* `git` (recommended with configured ssh)
* `cmake` 3.1 (minimal)
* `c++` compiler (checked on `clang-8`, `g++-8` and `g++-9`)
* `boost` 1.65 (minimal)
    * `unittests framework`
* `OpenGL`
* `GLUT`

## Deploy

### Ubuntu

Tested on: `18.04` and `20.04`

    $ sudo apt-get install libboost1.65-all-dev cmake make g++-8 freeglut3-dev
    $ git clone git@github.com:raidgar98/PS_TASK_3.git
    $ mkdir -p build && cd PS_TASK_3
    $ git submodule update --init --recursive
    $ cd ../build 
    $ cmake ../PS_TASK_3
    $ make -j8

### Windows

If everythink is properly setted up only cmake command is diffrent

    $ cmake -DUNIX=OFF ../PS_TASK_3

## Tests

    $ cd build/tests
    $ ctest -l all

## Debug mode

If you want to debug add following flag to cmake:

    -DCMAKE_BUILD_TYPE=Debug

recommended tool is `gdb`