
#pragma once

#include "core.hpp"

#include "stream/generator.hpp"
#include "stream/ints.hpp"
#include "stream/pipe.hpp"
#include "stream/stream.hpp"

#include "stream/chain.hpp"
#include "stream/drop.hpp"
#include "stream/filter.hpp"
#include "stream/map.hpp"
#include "stream/take.hpp"

#include "stream/collect.hpp"
#include "stream/fold.hpp"

//
// TODO(jtomschroeder):
// - max: (fold?)
// - drop (change to 'skip')
// - list comprehension
// - stream -> iter(): useable with for-range loop
// - reversable streams
// - chain-able streams
// - collect()
//
