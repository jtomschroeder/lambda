
#include "gmock/gmock.h"
#include "lambda.hpp"

#include <memory>

namespace lmd = lambda;

auto add = [](auto x, auto y) { return x + y; };

TEST(lambda, bind) {
   ASSERT_EQ(lmd::bind(add)(1, 2), 3);
   ASSERT_EQ(lmd::bind(add, 1)(2), 3);
   ASSERT_EQ(lmd::bind(add, 1, 2)(), 3);
}

struct Thing {
   auto fn(int x, int y, int z) {
      return x + y + z;
   }

   auto cfn(int x, int y, int z) const {
      return x + y + z;
   }
};

TEST(lambda, bind_mem_fn) {
   Thing thing;
   ASSERT_EQ(lmd::bind(&Thing::fn)(&thing, 1, 2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, &thing)(1, 2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, &thing, 1)(2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, &thing, 1, 2)(3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, &thing, 1, 2, 3)(), 6);
}

TEST(lambda, bind_mem_fn_smart_ptr) {
   auto thing = std::make_shared<Thing>();

   ASSERT_EQ(lmd::bind(&Thing::fn)(thing, 1, 2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, thing)(1, 2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, thing, 1)(2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, thing, 1, 2)(3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, thing, 1, 2, 3)(), 6);

   ASSERT_EQ(lmd::bind(&Thing::cfn)(thing, 1, 2, 3), 6);
}

TEST(lambda, bind_mem_fn_const_smart_ptr) {
   let thing = std::make_shared<Thing>();

   ASSERT_EQ(lmd::bind(&Thing::fn)(thing, 1, 2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, thing)(1, 2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, thing, 1)(2, 3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, thing, 1, 2)(3), 6);
   ASSERT_EQ(lmd::bind(&Thing::fn, thing, 1, 2, 3)(), 6);

   ASSERT_EQ(lmd::bind(&Thing::cfn)(thing, 1, 2, 3), 6);
}
