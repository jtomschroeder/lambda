
#ifndef LAMBDA_TYPE_TRAITS_H
#define LAMBDA_TYPE_TRAITS_H

#include <type_traits>
#include "function_traits.hpp"

namespace lambda {

template <typename T>
struct has_iterator {
   template <typename U>
   static char test(typename U::iterator *x);

   template <typename U>
   static long test(U *x);

   static const bool value = sizeof(test<T>(0)) == 1;
};

struct nope {};

template <typename F, typename... Args>
struct is_callable {
private:
   template <typename G, typename... Qs>
   static auto check(G &&g, Qs &&... qs) -> decltype(g(qs...));

   static nope check(...);

public:
   static constexpr bool value =
       !std::is_same<nope, decltype(check(std::declval<F>(),
                                          std::declval<Args>()...))>::value;

   using type = decltype(check(std::declval<F>(), std::declval<Args>()...));
};

template <typename F, typename... Args>
constexpr bool is_callable_v = is_callable<F, Args...>::value;

} /* lambda */

#endif // LAMBDA_TYPE_TRAITS_H
