
#include "gmock/gmock.h"
#include "lambda.hpp"

namespace lmd = lambda;

static auto mul(int x, int y, int z) {
   return x * y * z;
}

TEST(lambda, apply) {
   auto args = std::make_tuple(2, 4, 5);
   ASSERT_EQ(lmd::apply(mul, args), 40);
}

TEST(lambda, compose) {
   auto triple = [](auto i) { return i * 3; };
   auto triple_mul = lmd::compose(triple, mul);
   ASSERT_EQ(triple_mul(1, 2, 3), 18);
}

TEST(lambda, function_traits) {
   using std::is_same;

   using trait = lmd::function_traits<decltype(mul)>;
   static_assert(trait::arity == 3, "");
   static_assert(is_same<trait::return_t, int>::value, "");
   static_assert(is_same<trait::argument_t<0>, int>::value, "");
   static_assert(is_same<trait::argument_t<1>, int>::value, "");
}
