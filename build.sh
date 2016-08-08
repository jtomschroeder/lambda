#!/usr/bin/env bash

mkdir -p build && cd build

if [ ! -f Makefile ]; then
  cmake  ..
fi

make $@
