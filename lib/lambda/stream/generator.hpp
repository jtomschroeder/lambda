
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

template <class G>
class Generator : public Stream {
    G gen;

public:
    using Type = std::result_of_t<decltype(std::declval<G>)>;

    Generator(G gen) : gen(gen) {}

    Maybe<Type> next() { return some(gen()); }
};

template <class G>
auto generator(G gen) {
    return Generator<G>{gen};
}

} /* streams */
} /* lambda */
