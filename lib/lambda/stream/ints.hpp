
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

template <class I, REQUIRE_CONCEPT(std::is_convertible<I, int>::value)>
class IntsRangeStream : public Stream {
    I begin, end;

public:
    using Type = I;

    IntsRangeStream(I begin, I end) : begin(begin), end(end) {}

    Maybe<Type> next() { return begin < end ? some(begin++) : none; }
};

template <class I>
auto ints(I begin, I end) {
    return IntsRangeStream<I>{begin, end};
}

template <class I>
auto closed_ints(I begin, I end) {
    return IntsRangeStream<I>{begin, end + 1};
}

/////////////////////////

template <class I>
class IntsStream : public Stream {
    I begin;

public:
    using Type = I;

    explicit IntsStream(I begin) : begin(begin) {}

    Maybe<Type> next() { return some(begin++); }
};

template <class I>
auto ints(I begin) {
    return IntsStream<I>{begin};
}

} /* streams */
} /* lambda */
