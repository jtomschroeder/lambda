
#pragma once

#include "stream.hpp"
#include <mutex>

namespace lambda {
namespace streams {

template <class S, class I>
class DropStream : public Stream {
    S stream;
    const I num;
    std::shared_ptr<std::once_flag> flag;

public:
    using Type = typename S::Type;

    DropStream(S stream, I num) : stream(stream), num(num), flag(new std::once_flag) {}

    Maybe<Type> next() {
        std::call_once(*flag, [&]() {
            for (I i = 0; i < num; ++i) {
                if (stream.next() == none) {
                    break;
                }
            }
        });

        return stream.next();
    }
};

template <class I>
class Drop : public Pipeable {
    const I num;

public:
    Drop(I num) : num(num) {}

    template <class S>
    auto pipe(S stream) const {
        return DropStream<S, I>{stream, num};
    }
};

template <class I>
auto drop(I i) {
    return Drop<I>{i};
}

} /* streams */
} /* lambda */
