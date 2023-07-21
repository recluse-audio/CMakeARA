#!/bin/bash


rm -rf build
mkdir build
pushd build
cmake -DCMAKE_BUILD_TYPE=Debug -DPLUGIN_FORMATS="VST3" ..
cmake --build . --target CMakeARA
popd # back to top level