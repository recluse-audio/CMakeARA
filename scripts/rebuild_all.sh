#!/bin/sh

cd ../
rm -rf build
mkdir build
pushd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . 
popd # back to top level
