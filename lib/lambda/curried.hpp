
#ifndef LAMBDA_CURRIED_H
#define LAMBDA_CURRIED_H

#include "curry.hpp"

namespace lambda {

let plus = curry(std::plus<>{});

let multipleOf = curry(flip([](auto x, auto y) { return x % y == 0; }));
let even = multipleOf(2);

} /* lambda */

#endif // LAMBDA_CURRIED_H
