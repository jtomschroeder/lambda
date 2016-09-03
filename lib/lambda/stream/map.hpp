
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

using namespace lambda::monad;

template <class S, class F>
class MapStream : public Stream {
    S stream;
    F fn;

public:
    using Type = decltype(fn(std::declval<typename S::Type>()));

    MapStream(S stream, F fn) : stream(std::move(stream)), fn(fn) {}

    auto next() { return std::move(stream.next()) >> fn; }
};

template <class F>
class Map : public Pipeable {
    F f;

public:
    explicit Map(F f) : f(f) {}

    template <class S>
    auto pipe(S stream) const {
        return MapStream<S, F>{stream, f};
    }
};

template <class F>
auto map(F &&f) {
    return Map<F>{std::forward<F>(f)};
}

} /* streams */
} /* lambda */
