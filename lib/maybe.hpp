
#ifndef LAMBDA_MAYBE_H
#define LAMBDA_MAYBE_H

#include <experimental/optional>

namespace lambda {

template <typename T>
using Maybe = std::experimental::optional<T>;

template <class T>
constexpr auto some(T &&value) {
    return Maybe<typename std::decay<T>::type>(std::forward<T>(value));
}

constexpr auto none = std::experimental::nullopt;

template <class T, class F>
auto operator>>(Maybe<T> lhs, F &&fn) {
    return lhs ? fn(*lhs) : none;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Maybe<T> m) {
    if (m) {
        os << "Some(" << *m << ")";
    } else {
        os << "None";
    }
    return os;
}

} /* lambda */

#endif // LAMBDA_MAYBE_H
