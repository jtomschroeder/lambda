
#pragma once

#include "function_traits.hpp"
#include <type_traits>

namespace lambda {

namespace detail {
struct nope {};
}

//
// iterator has T.begin() and T.end()
// TODO! T::value_type, T.begin()++
//
template <typename T>
struct is_iterator {
private:
    template <typename G>
    static auto check(G &&g) -> std::pair<decltype(g.begin()), decltype(g.end())>;

    static detail::nope check(...);

public:
    static constexpr bool value =
        !std::is_same<detail::nope, decltype(check(std::declval<T>()))>::value;
};

template <typename T>
constexpr bool is_iterator_v = is_iterator<T>::value;

template <typename F, typename... Args>
struct is_callable {
private:
    template <typename G, typename... Qs>
    static auto check(G &&g, Qs &&... qs) -> decltype(g(qs...));

    static detail::nope check(...);

public:
    using type = decltype(check(std::declval<F>(), std::declval<Args>()...));

    static constexpr bool value =
        !std::is_same<detail::nope,
                      decltype(check(std::declval<F>(), std::declval<Args>()...))>::value;
};

template <typename F, typename... Args>
constexpr bool is_callable_v = is_callable<F, Args...>::value;

template <typename F, typename... Args>
using is_callable_t = typename is_callable<F, Args...>::type;

} /* lambda */
