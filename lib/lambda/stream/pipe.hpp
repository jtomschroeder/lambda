
#pragma once

namespace lambda {
namespace streams {

struct Pipeable {
    template <typename Arg, typename Pipeable>
    static auto pipeable(Arg &&arg, Pipeable pipeable) {
        return pipeable.pipe(std::forward<Arg>(arg));
    }
};

template <typename T>
struct is_pipeable : std::is_base_of<Pipeable, T> {};

////////////////////

template <typename Arg, typename Pipeable,
          REQUIRE_CONCEPT(!is_pipeable<Arg>() && is_pipeable<Pipeable>())>
auto operator|(Arg &&arg, Pipeable pipe) {
    return Pipeable::pipeable(std::forward<Arg>(arg), pipe);
}

} /* streams */
} /* lambda */
