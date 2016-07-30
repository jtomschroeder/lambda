
#ifndef LAMBDA_COMPOSE_H
#define LAMBDA_COMPOSE_H

#include "type_traits.hpp"

namespace lambda {

template <typename F, typename G>
auto compose(F f, G g) {
    return [f, g](auto &&... ps) { return f(g(std::forward<decltype(ps)>(ps)...)); };
}

} /* lambda */

#endif // LAMBDA_COMPOSE_H
