
#ifndef LAMBDA_MONAD_H
#define LAMBDA_MONAD_H

#include "maybe.hpp"

namespace lambda {

template <class T, class F>
auto operator>>(const Maybe<T> &m, F &&f) {
    return m ? some(f(*m)) : none;
}

} /* lambda */

#endif // LAMBDA_MONAD_H
