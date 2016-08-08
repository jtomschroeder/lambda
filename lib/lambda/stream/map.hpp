
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

template <class S, class F>
class MapStream : public Stream {
    S stream;
    F fn;

public:
    using Type = typename S::Type;

    MapStream(S stream, F fn) : stream(stream), fn(fn) {}

    Maybe<Type> next() { return stream.next() >> fn; }
};

template <class F>
class Map : public Pipeable {
    F f;

public:
    Map(F f) : f(f) {}

    template <class T>
    auto operator()(T value) const {
        return MapStream<T, F>{value, f};
    }
};

template <class F>
auto map(F &&f) {
    return Map<F>{std::forward<F>(f)};
}

} /* streams */
} /* lambda */
