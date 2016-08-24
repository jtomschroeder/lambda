
#pragma once

#include "lambda.hpp"

namespace lambda {
namespace streams {

template <template <typename, typename...> class T>
class Collect : public Pipeable {
public:
    Collect() {}

    template <class S>
    auto pipe(S &&stream) const {
        T<typename S::Type> collection;
        while (auto s = std::move(stream.next())) {
            collection.push_back(*s);
        }
        return collection;
    }
};

template <template <typename, typename...> class T = std::vector>
auto collect() {
    return Collect<T>{};
}

} /* streams */
} /* lambda */
