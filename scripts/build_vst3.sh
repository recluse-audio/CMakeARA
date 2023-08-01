#!/bin/bash



pushd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --target CMakeARA_VST3
popd # back to top level