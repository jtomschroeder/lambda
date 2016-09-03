
#pragma once

#include "variant.hpp"

namespace lambda {

template <class T>
struct Some {
    Some(T value) : value(new T{std::move(value)}) {}

    constexpr bool operator==(const Some<T> &s) const {
        assert(value && s.value);
        return *value == *s.value;
    }

    std::shared_ptr<T> value;
};

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
    using Some = Some<T>;

    Maybe() : value(None{}) {}
    Maybe(None none) : value(none) {}

    Maybe(Some some) : value(some) {}

    template <class U>
    Maybe(U val) : Maybe(Some{val}) {}

    constexpr const T &operator*() const & { return *value.template target<Some>()->value; }

    constexpr explicit operator bool() const { return value.which() == 0u; }

    constexpr bool operator==(const Maybe<T> &m) const { return value == m.value; }

private:
    variant<Some, None> value;
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
