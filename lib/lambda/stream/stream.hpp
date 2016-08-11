
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

template <class C>
class CollectionStream : public Stream {
    C collection;
    typename C::const_iterator begin, end;

public:
    using Type = typename C::value_type;

    CollectionStream(C &&collection)
        : collection(collection), begin(collection.cbegin()), end(collection.cend()) {}

    Maybe<Type> next() { return begin != end ? some(std::move(*begin++)) : none; }
};

template <class C, REQUIRE_CONCEPT(has_iterator_v<C>)>
auto stream(C &&c) {
    return CollectionStream<C>{std::forward<C>(c)};
}

template <class F>
class FunctionStream : public Stream {
    F f;

public:
    using Type = typename std::result_of_t<decltype(std::declval<F>)>::value_type; // Maybe::Type

    FunctionStream(F &&f) : f(f) {}

    Maybe<Type> next() { return f(); }
};

template <class F, class = std::enable_if_t<is_callable_v<F>>>
auto stream(F &&f) {
    return FunctionStream<F>{std::forward<F>(f)};
}

} /* streams */
} /* lambda */
