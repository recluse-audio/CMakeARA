#!/bin/sh

rm -rf build
mkdir build
pushd build
cmake -G Xcode ..
popd # back to top level

open build/*.xcodeproj


