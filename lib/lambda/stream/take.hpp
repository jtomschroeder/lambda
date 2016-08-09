
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

template <class S, class I>
class TakeStream : public Stream {
    S stream;
    I count;
    const I num;

public:
    using Type = typename S::Type;

    TakeStream(S stream, I num) : stream(stream), count(0), num(num) {}

    Maybe<Type> next() { return count++ < num ? stream.next() : none; }
};

template <class I>
class Take : public Pipeable {
    const I num;

public:
    Take(I num) : num(num) {}

    template <class S>
    auto pipe(S stream) const {
        return TakeStream<S, I>{stream, num};
    }
};

template <class I>
auto take(I i) {
    return Take<I>{i};
}

} /* streams */
} /* lambda */
