#!/usr/bin/env bash

rm -rf build

mkdir build
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"


cmake --build build


