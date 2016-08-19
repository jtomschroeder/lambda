
#pragma once

#include "type_traits.hpp"

namespace lambda {

// Note: <experimental/tuple> (library fundamentals TS)

template <typename F, typename G>
auto compose(F f, G g) {
    return [f, g](auto &&... ps) { return f(g(std::forward<decltype(ps)>(ps)...)); };
}

} /* lambda */
