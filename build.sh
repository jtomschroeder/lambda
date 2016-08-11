#!/usr/bin/env bash

mkdir -p build && cd build

if [ ! -f Makefile ]; then
  cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
fi

make $@
