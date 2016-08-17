
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
    explicit Take(I num) : num(num) {}

    template <class S>
    auto pipe(S stream) const {
        return TakeStream<S, I>{stream, num};
    }
};

template <class I>
auto take(I i) {
    return Take<I>{i};
}

////////////////////

template <class S, class P>
class TakeWhileStream : public Stream {
    S stream;
    P pred;

public:
    using Type = typename S::Type;

    TakeWhileStream(S stream, P pred) : stream(std::move(stream)), pred(std::move(pred)) {}

    Maybe<Type> next() {
        if (auto s = stream.next()) {
            return pred(*s) ? s : none;
        } 
            return none;
        
    }
};

template <class P>
class TakeWhile : public Pipeable {
    P pred;

public:
    explicit TakeWhile(P pred) : pred(std::move(pred)) {}

    template <class S>
    auto pipe(S stream) const {
        return TakeWhileStream<S, P>{stream, pred};
    }
};

template <class P>
auto take_while(P pred) {
    return TakeWhile<P>{pred};
}

} /* streams */
} /* lambda */
