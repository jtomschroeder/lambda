
#pragma once

#include "variant.hpp"

namespace lambda {

struct None {
    constexpr bool operator==(const None &) const { return true; }

    // None is equal only to None, unless otherwise specified.
    template <class T>
    constexpr bool operator==(const T &) const {
        return false;
    }
};

template <typename T>
struct Maybe {
    using Some = std::shared_ptr<T>;

    Maybe() : var(None{}) {}
    Maybe(None none) : var(none) {}

    Maybe(T some) : var(Some(new T{std::move(some)})) {}

    constexpr const T &value() const & { return *var.template target<Some>()->get(); }

    constexpr const T &operator*() const & { return *var.template target<Some>()->get(); }

    constexpr bool is_some() const { return var.which() == 0u; }
    constexpr bool is_none() const { return var.which() == 1u; }

    constexpr explicit operator bool() const { return is_some(); }

    constexpr bool operator==(const Maybe<T> &m) const {
        return var.which() == m.var.which() && (is_none() || value() == m.value());
    }

private:
    variant<Some, None> var;
};

template <class T>
constexpr auto some(T value) {
    using Type = typename std::decay<T>::type;
    return Maybe<Type>{std::move(value)};
}

constexpr auto none = None{};

template <class T>
constexpr bool operator==(const None &, const Maybe<T> &m) {
    return !bool(m);
}

} /* lambda */
