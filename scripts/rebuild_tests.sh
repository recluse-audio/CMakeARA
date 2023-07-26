#!/bin/bash

rm -rf build
mkdir build
pushd build
cmake  ..
cmake --build . --target Tests
popd # back to top level

ctest --verbose