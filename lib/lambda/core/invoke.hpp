
#pragma once

#include <type_traits>

namespace lambda {

// Note: since C++17

namespace detail {
template <class F, class... Args>
auto INVOKE(F &&f, Args &&... args) -> decltype(std::forward<F>(f)(std::forward<Args>(args)...)) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <class Base, class T, class Derived>
auto INVOKE(T Base::*pmd, Derived &&ref) -> decltype(std::forward<Derived>(ref).*pmd) {
    return std::forward<Derived>(ref).*pmd;
}

template <class PMD, class Pointer>
auto INVOKE(PMD pmd, Pointer &&ptr) -> decltype((*std::forward<Pointer>(ptr)).*pmd) {
    return (*std::forward<Pointer>(ptr)).*pmd;
}

template <class Base, class T, class Derived, class... Args>
auto INVOKE(T Base::*pmf, Derived &&ref, Args &&... args)
    -> decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...)) {
    return (std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...);
}

template <class PMF, class Pointer, class... Args>
auto INVOKE(PMF pmf, Pointer &&ptr, Args &&... args)
    -> decltype(((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...)) {
    return ((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...);
}
}

template <class F, class... ArgTypes>
auto invoke(F &&f, ArgTypes &&... args) {
    return detail::INVOKE(std::forward<F>(f), std::forward<ArgTypes>(args)...);
}

} /* lambda */
