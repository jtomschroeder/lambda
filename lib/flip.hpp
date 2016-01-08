
#ifndef LAMBDA_FLIP_H
#define LAMBDA_FLIP_H

namespace lambda {

template <typename F>
auto flip(F f) {
   return [f](auto &&b, auto &&a) {
      return f(std::forward<decltype(a)>(a), std::forward<decltype(b)>(b));
   };
}

} /* lambda */

#endif // LAMBDA_FLIP_H
