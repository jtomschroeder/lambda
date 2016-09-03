
#pragma once

#include <eggs/variant.hpp>

namespace lambda {

template <class... Ts>
using variant = eggs::variant<Ts...>;

template <class... Ts>
auto visit(Ts... ts) {
    return eggs::variants::apply(std::forward<Ts>(ts)...);
}

} /* lambda */
