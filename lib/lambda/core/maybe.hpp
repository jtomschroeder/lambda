
#pragma once

#include <experimental/optional>

namespace lambda {

template <typename T>
using Maybe = std::experimental::optional<T>;

template <class T>
constexpr auto some(T value) {
    return Maybe<typename std::decay<T>::type>(std::move(value));
}

constexpr auto none = std::experimental::nullopt;

} /* lambda */
