#!/bin/bash

rm -rf build
mkdir build
pushd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --target CMakeARA
cmake --build . --target Tests
popd # back to top level
