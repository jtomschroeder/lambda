
#pragma once

#include "macros.hpp"
#include "type_traits.hpp"

#include <functional>
#include <tuple>

namespace lambda {

template <typename F, typename... BoundArgs>
struct Curried {
private:
    F f;
    std::tuple<typename std::remove_reference<BoundArgs>::type...> args;

    template <typename... Ts, REQUIRE_CONCEPT(is_callable_v<F, Ts...>)>
    auto dispatch(Ts &&... ts) const {
        return f(std::forward<Ts>(ts)...);
    }

    template <typename... Ts, REQUIRE_CONCEPT(!is_callable_v<F, Ts...>)>
    auto dispatch(Ts &&... ts) const {
        return Curried<F, Ts...>(f, std::forward<Ts>(ts)...);
    }

    template <std::size_t... Ns, typename... Ts>
    auto call(std::index_sequence<Ns...> /*unused*/, Ts &&... ts) const {
        return dispatch(std::get<Ns>(args)..., std::forward<Ts>(ts)...);
    }

public:
    explicit Curried(F f, BoundArgs &&... args)
        : f(std::move(f)), args(std::forward<BoundArgs>(args)...) {}

    template <typename... Ts>
    auto operator()(Ts &&... ts) const {
        return call(std::make_index_sequence<sizeof...(BoundArgs)>(), std::forward<Ts>(ts)...);
    }

    template <typename G>
    auto operator||(G g) const {
        return [this, g](auto &&... ps) {
            return this->operator()(std::forward<decltype(ps)>(ps)...) ||
                   g(std::forward<decltype(ps)>(ps)...);
        };
    }
};

template <typename F, typename... Ts, REQUIRE_CONCEPT(!std::is_member_function_pointer<F>() &&
                                                      !std::is_member_object_pointer<F>())>
auto curry(F &&f, Ts &&... ts) {
    return Curried<F, Ts...>(f, std::forward<Ts>(ts)...);
}

template <class R, class C, class... Args>
auto curry(R (C::*fn)(Args...)) {
    return Curried<std::function<R(C *, Args...)>>(
        [fn](C *c, Args &&... ps) { return (c->*fn)(std::forward<decltype(ps)>(ps)...); });
}

template <class R, class C, class... Args>
auto curry(R (C::*fn)(Args...) const) {
    return Curried<std::function<R(C *, Args...)>>(
        [fn](const C *c, Args &&... ps) { return (c->*fn)(std::forward<decltype(ps)>(ps)...); });
}

} /* lambda */
