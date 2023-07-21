#!/bin/bash

rm -rf build
mkdir build
pushd build
cmake -DCMAKE_BUILD_TYPE=Debug -DPLUGIN_FORMATS="AU VST3 Standalone" ..
cmake --build . --target Tests
popd # back to top level
