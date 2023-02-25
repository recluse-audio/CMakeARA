#!/bin/sh

rm -rf Builds
mkdir Builds
pushd Builds
cmake -G Xcode ..
popd # back to top level

open Builds/*.xcodeproj


