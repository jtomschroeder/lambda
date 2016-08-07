
#pragma once

#include "maybe.hpp"

namespace lambda {
namespace streams {

struct Pipeable {
    template <typename Arg, typename Pipe>
    static auto pipe(Arg &&arg, Pipe pipe) {
        return pipe(std::forward<Arg>(arg));
    }
};

template <typename T>
struct is_pipeable : std::is_base_of<Pipeable, T> {};

////////////////////

struct Stream {};

template <typename T>
struct is_stream : std::is_base_of<Stream, T> {};

template <class C>
class CollectionStream : public Stream {
    C collection;
    typename C::const_iterator begin, end;

public:
    using Type = typename C::value_type;

    CollectionStream(C &&collection)
        : collection(collection), begin(collection.cbegin()), end(collection.cend()) {}

    Maybe<Type> next() { return begin != end ? some(*begin++) : none; }
};

template <class C>
auto stream(C &&c) {
    return CollectionStream<C>{std::forward<C>(c)};
}

////////////////////

#define REQUIRE_CONCEPT(...) std::enable_if_t<(__VA_ARGS__), int> = 0

template <typename Arg, typename Pipe,
          REQUIRE_CONCEPT(!is_pipeable<Arg>() && is_stream<Arg>() && is_pipeable<Pipe>())>
auto operator|(Arg &&arg, Pipe pipe) {
    return Pipe::pipe(std::forward<Arg>(arg), pipe);
}

////////////////////

template <class S, class F>
class MapStream : public Stream {
    S stream;
    F fn;

public:
    using Type = typename S::Type;

    MapStream(S stream, F fn) : stream(stream), fn(fn) {}

    Maybe<Type> next() { return stream.next() >> fn; }
};

template <class F>
class Map : public Pipeable {
    F f;

public:
    Map(F f) : f(f) {}

    template <class T>
    auto operator()(T value) const {
        return MapStream<T, F>{value, f};
    }
};

template <class F>
auto map(F &&f) {
    return Map<F>{std::forward<F>(f)};
}

////////////////////

template <class S, class F>
class FilterStream : public Stream {
    S stream;
    F fn;

public:
    using Type = typename S::Type;

    FilterStream(S stream, F fn) : stream(stream), fn(fn) {}

    Maybe<Type> next() {
        while (auto s = stream.next()) {
            if (fn(std::cref(*s))) {
                return s;
            }
        }
        return none;
    }
};

template <class F>
class Filter : public Pipeable {
    F f;

public:
    Filter(F f) : f(f) {}

    template <class T>
    auto operator()(T value) const {
        return FilterStream<T, F>{value, f};
    }
};

template <class F>
auto filter(F &&f) {
    return Filter<F>{std::forward<F>(f)};
}

} /* streams */
} /* lambda */
