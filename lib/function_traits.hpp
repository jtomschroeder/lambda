
#ifndef LAMBDA_FUNCTION_TRAITS_H
#define LAMBDA_FUNCTION_TRAITS_H

#include <type_traits>

namespace lambda {

template <class F>
struct function_traits;

template <class R, class... Args>
struct function_traits<R (*)(Args...)> : public function_traits<R(Args...)> {};

template <class R, class... Args>
struct function_traits<R(Args...)> {
   using return_t = R;

   static constexpr std::size_t arity = sizeof...(Args);

   template <std::size_t N>
   struct argument {
      static_assert(N < arity, "error: invalid parameter index.");
      using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
   };

   template <std::size_t N>
   using argument_t = typename argument<N>::type;
};

// member function pointer
template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...)>
    : public function_traits<R(C &, Args...)> {};

// const member function pointer
template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const>
    : public function_traits<R(C &, Args...)> {};

// member object pointer
template <class C, class R>
struct function_traits<R(C::*)> : public function_traits<R(C &)> {};

// functor
template <class F>
struct function_traits {
private:
   using call_t = function_traits<decltype(&F::operator())>;

public:
   using return_t = typename call_t::return_t;

   static constexpr std::size_t arity = call_t::arity - 1;

   template <std::size_t N>
   struct argument {
      static_assert(N < arity, "error: invalid parameter index.");
      using type = typename call_t::template argument<N + 1>::type;
   };

   template <std::size_t N>
   using argument_t = typename argument<N>::type;
};

template <class F>
struct function_traits<F &> : public function_traits<F> {};

template <class F>
struct function_traits<F &&> : public function_traits<F> {};

} /* lambda */

#endif // LAMBDA_FUNCTION_TRAITS_H
