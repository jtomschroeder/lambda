#!/usr/bin/env bash

mkdir -p build && cd build

if [ ! -f Makefile ]; then
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
fi

make $@
