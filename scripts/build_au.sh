#!/bin/bash

pushd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --target CMakeARA_AU
popd 