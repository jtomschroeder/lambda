
#pragma once

#include "curry.hpp"

namespace lambda {

let plus = curry(std::plus<>{});
let less = curry(flip(std::less<>{}));

let multipleOf = curry(flip([](auto x, auto y) { return x % y == 0; }));
let even = multipleOf(2);

} /* lambda */
