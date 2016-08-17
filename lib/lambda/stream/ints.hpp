
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

template <class I, class J,
          REQUIRE_CONCEPT(std::is_convertible<I, int>() && std::is_convertible<J, int>())>
class IntsRangeStream : public Stream {
    I begin;
    J end;

public:
    using Type = std::common_type_t<I, J>;

    IntsRangeStream(I begin, J end) : begin(begin), end(end) {}

    Maybe<Type> next() { return begin < end ? some(begin++) : none; }
};

template <class I, class J>
auto ints(I begin, J end) {
    return IntsRangeStream<I, J>{begin, end};
}

template <class I, class J>
auto closed_ints(I begin, J end) {
    return IntsRangeStream<I, J>{begin, end + 1};
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
