
#pragma once

#include "invoke.hpp"

namespace lambda {

template <class Fn, class... Ts>
auto bind(Fn fn, Ts &&... ts) {
    return
        [fn, ts...](auto &&... ps) { return invoke(fn, ts..., std::forward<decltype(ps)>(ps)...); };
}

} /* lambda */
