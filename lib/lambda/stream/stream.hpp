
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

} /* streams */
} /* lambda */
