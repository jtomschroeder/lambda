
#pragma once

#include "function_traits.hpp"
#include <type_traits>

namespace lambda {

struct nope {};

template <typename T>
struct has_iterator {
    template <typename U>
    static char test(typename U::iterator *x);

    template <typename U>
    static long test(U *x);

    static const bool value = sizeof(test<T>(nullptr)) == 1;
};

template <typename T>
constexpr bool has_iterator_v = has_iterator<T>::value;

template <typename F, typename... Args>
struct is_callable {
private:
    template <typename G, typename... Qs>
    static auto check(G &&g, Qs &&... qs) -> decltype(g(qs...));

    static nope check(...);

public:
    static constexpr bool value =
        !std::is_same<nope, decltype(check(std::declval<F>(), std::declval<Args>()...))>::value;

    using type = decltype(check(std::declval<F>(), std::declval<Args>()...));
};

template <typename F, typename... Args>
constexpr bool is_callable_v = is_callable<F, Args...>::value;

} /* lambda */
