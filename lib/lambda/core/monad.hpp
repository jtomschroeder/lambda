
#pragma once

#include "maybe.hpp"

namespace lambda {
namespace monad {

template <class T, class F>
auto operator>>(const Maybe<T> &m, F &&f) {
    return m ? some(f(*m)) : none;
}

} // monad
} // lambda
