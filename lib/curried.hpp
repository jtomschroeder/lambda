
#ifndef LAMBDA_CURRIED_H
#define LAMBDA_CURRIED_H

#include "curry.hpp"

namespace lambda {

let plus = curry(std::plus<>{});

} /* lambda */

#endif // LAMBDA_CURRIED_H
