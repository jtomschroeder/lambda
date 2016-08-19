
#pragma once

#include "pipe.hpp"

namespace lambda {
namespace streams {

//
// `Stream` concept
//
struct Stream {
    using Type = void;
    Maybe<Type> next();
};

template <class R>
class Range : public Stream {
    R range;

    decltype(range.begin()) begin_;
    decltype(range.end()) end_;

public:
    using Type = typename R::value_type;

    explicit Range(R range) : range(range), begin_(range.begin()), end_(range.end()) {}

    Maybe<Type> next() { return begin_ != end_ ? some(std::move(*begin_++)) : none; }
};

template <class R, REQUIRE_CONCEPT(is_iterator_v<R>)>
auto stream(R range) {
    return Range<R>{std::move(range)};
}

template <class F>
class FunctionStream : public Stream {
    F f;

public:
    using Type = typename decltype(f())::value_type; // Maybe::Type

    explicit FunctionStream(F &&f) : f(f) {}

    Maybe<Type> next() { return f(); }
};

template <class F, REQUIRE_CONCEPT(is_callable_v<F>)>
auto stream(F &&f) {
    return FunctionStream<F>{std::forward<F>(f)};
}

} /* streams */
} /* lambda */
