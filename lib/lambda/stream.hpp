
#pragma once

#include "maybe.hpp"

namespace lambda {

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

template <class T>
class Stream : public std::enable_shared_from_this<Stream<T>> {
public:
    using RawStream = std::shared_ptr<Stream>;

    Stream() {}

    virtual Maybe<T> next() = 0;

    template <class F>
    RawStream map(F &&f);
};

template <class T>
using RawStream = typename Stream<T>::RawStream;

template <class T, class F>
class Map : public Stream<T> {
    RawStream<T> stream;
    F f;

public:
    Map(RawStream<T> stream, F f) : stream(stream), f(f) {}

    virtual Maybe<T> next() { return stream->next() >> f; }
};

template <class T, class C>
class IteratorStream : public Stream<T> {
    typename C::const_iterator begin, end;

public:
    IteratorStream(C &collection) : begin(collection.cbegin()), end(collection.cend()) {}

    virtual Maybe<T> next() { return begin != end ? some(*begin++) : none; }
};

template <class T, class C>
static auto from(C &collection) {
    return RawStream<T>(new IteratorStream<T, C>{collection});
}

template <class T>
template <class F>
RawStream<T> Stream<T>::map(F &&f) {
    return RawStream(new Map<T, F>{Stream<T>::shared_from_this(), f});
}

} /* lambda */
