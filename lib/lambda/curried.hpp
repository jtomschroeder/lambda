
#pragma once

#include "curry.hpp"

namespace lambda {

let plus = curry(std::plus<>{});
let minus = curry(std::minus<>{});
let multiplies = curry(std::multiplies<>{});
let divides = curry(std::divides<>{});
let modulus = curry(std::modulus<>{});
let negate = curry(std::negate<>{});

let less = curry(flip(std::less<>{}));

let multipleOf = curry(flip([](auto x, auto y) { return x % y == 0; }));
let even = multipleOf(2);

} /* lambda */
