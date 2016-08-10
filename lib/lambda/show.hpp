
#pragma once

#include "maybe.hpp"

namespace lambda {

inline std::string show(std::string s) { return s; }
inline std::string show(char c) { return std::string(1, c); }
inline std::string show(int i) { return std::to_string(i); }

template <class T>
std::string show(const Maybe<T> maybe) {
    return maybe ? "Some(" + show(*maybe) + ")" : "None";
}

template <class T>
std::string show(const std::vector<T> vec) {
    std::string os = "[";
    for (const auto &i : vec) {
        os += show(i);
        if (&i != &vec.back()) {
            os += ", ";
        }
    }
    os += "]";
    return os;
}

} /* lambda */
