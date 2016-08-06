
#pragma once

#include <type_traits>
#include "function_traits.hpp"

namespace lambda {
namespace dollar {

// pulled from dollarswift.org & Underscore.js

// Factories

template <class... Ts>
constexpr std::vector<std::common_type_t<Ts...>> vector(Ts &&... ts) {
    return {std::forward<Ts>(ts)...};
}

template <class... Ts>
constexpr auto array(Ts &&... ts) {
    return std::array<std::common_type_t<Ts...>, sizeof...(ts)>{std::forward<Ts>(ts)...};
}

/// Functions

template <class T>
constexpr T id(T &&value) {
    return std::forward<T>(value);
}

template <class R, class F>
auto map(R &&r, F &&f) {
    std::transform(r.begin(), r.end(), r.begin(), [&](auto i) { return f(i); });
    return r;
}

template <class R, class... Ts>
auto without(R r, const Ts &... ts) {
    auto filters = array(ts...);
    r.erase(std::remove_if(r.begin(), r.end(), [&](auto i) {
                return std::find(std::begin(filters), std::end(filters), i) != filters.end();
            }), r.end());
    return r;
}

} /* dollar */

namespace $ = dollar;

} /* lambda */
