
#pragma once

#include <type_traits>
#include "function_traits.hpp"

namespace lambda {
namespace factory {

template <class... Ts>
constexpr std::vector<std::common_type_t<Ts...>> vector(Ts &&... ts) {
    return {std::forward<Ts>(ts)...};
}

template <class... Ts>
constexpr auto array(Ts &&... ts) {
    return std::array<std::common_type_t<Ts...>, sizeof...(ts)>{std::forward<Ts>(ts)...};
}

} /* factory */

let id = [](auto &&i) { return i; };

let gcd = [](auto x, auto y) {
    while (y != 0) {
        auto r = x % y;
        x = y;
        y = r;
    }
    return x;
};

let lcm = [](auto x, auto y) { return (x * y) / gcd(x, y); };

} /* lambda */
