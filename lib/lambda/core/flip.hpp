
#pragma once

#include <utility>

namespace lambda {

template <typename F>
auto flip(F f) {
    return [f](auto &&b, auto &&a) {
        return f(std::forward<decltype(a)>(a), std::forward<decltype(b)>(b));
    };
}

} /* lambda */
