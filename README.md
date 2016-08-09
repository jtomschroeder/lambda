# λ

`lambda` is a functional library for C++

[![Build Status](https://travis-ci.org/jtomschroeder/lambda.svg?branch=master)](https://travis-ci.org/jtomschroeder/lambda)

### Usage
```cpp
using namespace lambda;

let multipleOf = curry(flip([](auto x, auto y) { return x % y == 0; }));
let even = multipleOf(2);

// ...

using namespace lambda::streams;

// Find the sum of all the multiples of 3 or 5 below 1000.
ints(0, 1000) | filter(multipleOf(3) || multipleOf(5)) | sum;
```

### About

`lambda` brings the power of __currying__ and other functional paradigms to C++, in a simple library. The goal: making functional programming in C++ *straight-forward* and *intuitive*.

__Features__
- currying
- function composition
- partial application (simplified functional `bind`)
- streams
