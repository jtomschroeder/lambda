
#pragma once

#include "stream.hpp"

namespace lambda {
namespace streams {

template <class S, class C>
class ChainStream : public Stream {
    S stream;
    C chain;

public:
    using Type = std::common_type_t<typename S::Type, typename C::Type>;

    ChainStream(S &&stream, C chain) : stream(std::move(stream)), chain(std::move(chain)) {}

    Maybe<Type> next() {
        if (auto s = std::move(stream.next())) {
            return s;
        }

        return std::move(chain.next());
    }
};

template <class C>
class Chain : public Pipeable {
    C chain;

public:
    explicit Chain(C chain) : chain(std::move(chain)) {}

    template <class S>
    auto pipe(S &&stream) const {
        return ChainStream<S, C>{std::move(stream), chain};
    }
};

template <class S>
auto chain(S &&stream) {
    return Chain<S>{std::forward<S>(stream)};
}

} /* streams */
} /* lambda */
