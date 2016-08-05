
#ifndef LAMBDA_SHOW_H
#define LAMBDA_SHOW_H

#include "maybe.hpp"

namespace lambda {

template <class T>
std::ostream &operator<<(std::ostream &os, const Maybe<T> m) {
    if (m) {
        os << "Some(" << *m << ")";
    } else {
        os << "None";
    }
    return os;
}

} /* lambda */

#endif // LAMBDA_SHOW_H
