
#ifndef LAMBDA_APPLY_H
#define LAMBDA_APPLY_H

#include "invoke.hpp"

#include <array>
#include <utility>

namespace lambda {

namespace detail {
template <class F, class Tuple, std::size_t... I>
constexpr auto apply(F &&f, Tuple &&t, std::index_sequence<I...>) {
    return invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
}
}

template <class F, class Tuple>
constexpr auto apply(F &&f, Tuple &&t) {
    return detail::apply(std::forward<F>(f), std::forward<Tuple>(t),
                         std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>{}>{});
}

} /* lambda */

#endif // LAMBDA_APPLY_H
