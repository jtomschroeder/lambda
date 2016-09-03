
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "maybe.hpp"

namespace lambda {

inline std::string show(std::string s) { return s; }
inline std::string show(char c) { return std::string(1, c); }

template <class I, REQUIRE_CONCEPT(std::is_convertible<I, int>())>
std::string show(I i) {
    return std::to_string(i);
}

inline std::string show(const None &) { return "None"; }

template <class T>
std::string show(const Maybe<T> &maybe) {
    return maybe ? "Some(" + show(*maybe) + ")" : "None";
}

template <class T>
std::string show(const std::vector<T> &vec) {
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

// TODO! tuple
// TODO! map

template <class K, class V>
std::string show(const std::pair<K, V> &pair) {
    return show(pair.first) + " +> " + show(pair.second);
}

template <class K, class V>
std::string show(const std::unordered_map<K, V> &map) {
    std::string os = "{ ";

    size_t count = 0;
    for (auto it = map.begin(), end = map.end(); it != end; ++it, ++count) {
        os += show(*it);

        if (count + 1 != map.size()) {
            os += ", ";
        }
    }

    os += " }";
    return os;
}

} /* lambda */
