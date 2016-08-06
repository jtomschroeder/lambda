
#pragma once

#include <type_traits>
#include "function_traits.hpp"

namespace lambda {

// pulled from dollarswift.org

class Dollar {
public:
    Dollar() {}

    /// Functions

    template <class R, class F>
    auto map(R &&r, F &&f) const {
        std::transform(r.begin(), r.end(), r.begin(), [&](auto i) { return f(i); });
        return r;
    }

    template <class R, class... Ts>
    auto without(R r, const Ts &... ts) const {
        auto filters = {ts...};
        r.erase(std::remove_if(r.begin(), r.end(), [&](auto i) {
                    return filters.find(i) != filters.end();
                }), r.end());
        return r;
    }

    // Factories

    template <class... Ts>
    constexpr std::vector<std::common_type_t<Ts...>> vector(Ts &&... ts) const {
        return {std::forward<Ts>(ts)...};
    }

    template <class... Ts>
    constexpr auto array(Ts &&... ts) const {
        return std::array<std::common_type_t<Ts...>, sizeof...(ts)>{std::forward<Ts>(ts)...};
    }
};

static const Dollar $;

} /* lambda */
