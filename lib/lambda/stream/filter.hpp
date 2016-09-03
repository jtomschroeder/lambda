
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

template <class S, class F>
class FilterStream : public Stream {
    S stream;
    F fn;

public:
    using Type = typename S::Type;

    FilterStream(S &&stream, F fn) : stream(std::move(stream)), fn(std::move(fn)) {}

    Maybe<Type> next() {
        while (auto s = std::move(stream.next())) {
            if (fn(*s)) {
                return s;
            }
        }
        return none;
    }
};

template <class F>
class Filter : public Pipeable {
    F f;

public:
    explicit Filter(F f) : f(std::move(f)) {}

    template <class S>
    auto pipe(S &&stream) const {
        return FilterStream<S, F>{std::move(stream), f};
    }
};

template <class F>
auto filter(F &&f) {
    return Filter<F>{std::forward<F>(f)};
}

} /* streams */
} /* lambda */
