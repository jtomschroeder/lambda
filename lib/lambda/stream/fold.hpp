
#pragma once

#include "lambda.hpp"

namespace lambda {
namespace streams {

template <class I, class F>
class Fold : public Pipeable {
    I initial;
    F f;

public:
    Fold(I &&initial, F &&f) : initial(initial), f(f) {}

    template <class S>
    auto pipe(S &&stream) const {
        auto init = initial;
        while (auto s = std::move(stream.next())) {
            init = f(init, *s);
        }
        return init;
    }
};

template <class I, class F>
auto fold(I &&initial, F &&f) {
    return Fold<I, F>{std::forward<I>(initial), std::forward<F>(f)};
}

let sum = fold(0, plus);

} /* streams */
} /* lambda */
