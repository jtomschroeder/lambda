
#ifndef LAMBDA_MONAD_H
#define LAMBDA_MONAD_H

#include "maybe.hpp"

namespace lambda {

template <class T, class F>
std::result_of_t<F(T)> operator>>(const Maybe<T> &m, F &&f) {
    return m ? f(*m) : none;
}

} /* lambda */

#endif // LAMBDA_MONAD_H
