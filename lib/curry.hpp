
#ifndef LAMBDA_CURRY_H
#define LAMBDA_CURRY_H

#include "type_traits.hpp"
#include <tuple>

namespace lambda {

template <typename F, typename... BoundArgs>
struct Curried {
private:
   F f;
   std::tuple<typename std::remove_reference<BoundArgs>::type...> args;

   template <typename... Ts, class = std::enable_if_t<is_callable_v<F, Ts...>>>
   auto dispatch(Ts &&... ts) const -> std::result_of_t<F(Ts...)> {
      return f(std::forward<Ts>(ts)...);
   }

   template <typename... Ts, class = std::enable_if_t<!is_callable_v<F, Ts...>>>
   auto dispatch(Ts &&... ts) const {
      return Curried<F, Ts...>(f, std::forward<Ts>(ts)...);
   }

   template <std::size_t... Ns, typename... Ts>
   auto call(std::index_sequence<Ns...>, Ts &&... ts) const {
      return dispatch(std::get<Ns>(args)..., std::forward<Ts>(ts)...);
   }

public:
   Curried(F f, BoundArgs &&... args)
      : f(f), args(std::forward<BoundArgs>(args)...) {}

   template <typename... Ts>
   auto operator()(Ts &&... ts) const {
      return call(std::make_index_sequence<sizeof...(BoundArgs)>(),
                  std::forward<Ts>(ts)...);
   }

   template <typename G>
   auto operator||(G g) {
      return [this, g](auto &&... ps) {
         return this->operator()(std::forward<decltype(ps)>(ps)...) ||
                g(std::forward<decltype(ps)>(ps)...);
      };
   }
};

template <typename F, typename... Ts,
          class = std::enable_if_t<!std::is_member_function_pointer<F>::value>,
          class = std::enable_if_t<!std::is_member_object_pointer<F>::value>>
auto curry(F &&f, Ts &&... ts) {
   return Curried<F, Ts...>(f, std::forward<Ts>(ts)...);
}

template <class R, class C, class... Args>
auto curry(R (C::*fn)(Args...)) {
   return Curried<std::function<R(C *, Args...)>>([fn](C *c, Args &&... ps) {
      return (c->*fn)(std::forward<decltype(ps)>(ps)...);
   });
}

template <class R, class C, class... Args>
auto curry(R (C::*fn)(Args...) const) {
   return Curried<std::function<R(C *, Args...)>>(
       [fn](const C *c, Args &&... ps) {
          return (c->*fn)(std::forward<decltype(ps)>(ps)...);
       });
}

} /* lambda */

#endif // LAMBDA_CURRY_H
