
#pragma once

#include "curry.hpp"

namespace lambda {

// Arithmetic operations

let plus = curry(std::plus<>{});
let minus = curry(std::minus<>{});
let multiplies = curry(std::multiplies<>{});
let divides = curry(std::divides<>{});
let modulus = curry(std::modulus<>{});
let negate = curry(std::negate<>{});

// Comparisons

let less = curry(flip(std::less<>{}));

// Miscellaneous

let multipleOf = curry(flip([](auto x, auto y) { return x % y == 0; }));
let even = multipleOf(2);

} /* lambda */
