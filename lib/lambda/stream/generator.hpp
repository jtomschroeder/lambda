
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

template <class G>
class Generator : public Stream {
    G gen;

public:
    using Type = decltype(gen());

    explicit Generator(G gen) : gen(std::move(gen)) {}

    Maybe<Type> next() { return some(gen()); }
};

template <class G>
auto generator(G gen) {
    return Generator<G>{gen};
}

} /* streams */
} /* lambda */
