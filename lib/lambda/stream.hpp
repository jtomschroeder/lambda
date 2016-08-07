
#pragma once

#include "maybe.hpp"

namespace lambda {
namespace streams {

// pub trait Iterator {
//     type Item;
//     fn next(&mut self)->Option<Self::Item>;
//
// fn map<B, F>(self, f: F) -> Map<Self, F> where Self: Sized, F: FnMut(Self::Item) -> B { ... }
//
//
// pub struct Map<I, F> {
//     iter: I,
//     f: F,
// }
//

/////////////////////////

template <typename T>
struct static_const {
    static constexpr T value{};
};

/// \ingroup group-utility
/// \sa `static_const`
template <typename T>
constexpr T static_const<T>::value;

#define DEFINE_INLINE_VARIABLE(type, name)                                                         \
    inline namespace { constexpr auto &name = static_const<type>::value; }

/////////////////////////

struct pipeable_base {};

template <typename T>
struct is_pipeable : std::is_base_of<pipeable_base, T> {};

struct pipeable : pipeable_base {
    template <typename Arg, typename Pipe>
    static auto pipe(Arg &&arg, Pipe pipe) {
        return pipe(std::forward<Arg>(arg));
    }
};

template <class C>
class Stream {
    C collection;
    typename C::const_iterator begin, end;

public:
    Stream(C &&collection)
        : collection(collection), begin(collection.cbegin()), end(collection.cend()) {}

    auto next() { return begin != end ? some(*begin++) : none; }
};

template <class C>
std::string show(const Stream<C> stream) {
    return "Stream";
}

template <class C>
auto stream(C &&c) {
    return Stream<C>{std::forward<C>(c)};
}

template <class S, class F>
class MapStream {
    S stream;
    F map_fn;

public:
    MapStream(S stream, F map_fn) : stream(stream), map_fn(map_fn) {}

    auto next() { return stream.next() >> map_fn; }
};

template <class S, class F>
std::string show(const MapStream<S, F> stream) {
    return "MapStream";
}

template <class F>
struct Map : pipeable {
    F f;
    Map(F f) : f(f) {}

    template <class T>
    auto operator()(T value) const {
        return MapStream<T, F>{value, f};
    }
};

// DEFINE_INLINE_VARIABLE(Map, map)

template <class F>
auto map(F &&f) {
    return Map<F>{std::forward<F>(f)};
}

// Evaluate the pipe with an argument
template <typename Arg, typename Pipe,
          std::enable_if_t<!is_pipeable<Arg>() && is_pipeable<Pipe>(), int> = 0>
auto operator|(Arg &&arg, Pipe pipe) {
    return Pipe::pipe(std::forward<Arg>(arg), pipe);
}

} /* streams */
} /* lambda */
