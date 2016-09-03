#!/usr/bin/env bash

set -e
set -o pipefail

MAKE=make # ninja

MODE=build
CLEAN=0

usage()
{
   echo "build.sh !!!"
}

#
# Handle command line options
#
until [[ -z "$@" ]]; do
  case $1 in
    build | verify | perf | demo)
      MODE=$1
      ;;
    -c | --clean)
      CLEAN=1
      ;;
    --)
      # leave remaining $@
      break
      ;;
    -h | --help)
      usage
      exit
      ;;
    *)
      echo "Error: ${1} is not a valid option."
      usage
      exit
      ;;
  esac
  shift
done

configure()
{
  if [ ! -d .vendor ]; then
    git clone https://github.com/google/googletest.git  .vendor/googletest
    git clone https://github.com/google/benchmark.git   .vendor/benchmark
    git clone https://github.com/eggs-cpp/variant       .vendor/variant
  fi

  if [[ ! -d .build ]] || [[ $CLEAN -eq 1 ]]; then
    rm -rf .build
    mkdir -p .build && cd .build

    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
    cd -
  fi
}

case $MODE in
  build)
    configure
    $MAKE
    ;;
  verify)
    configure
    $MAKE -C .build/ verify
    .build/test/verify $@
    ;;
  perf)
    configure
    $MAKE -C .build/ perf
    .build/bench/perf $@
    ;;
  demo)
    configure
    $MAKE -C .build/ demo
    .build/demo/demo $@
    ;;
esac
