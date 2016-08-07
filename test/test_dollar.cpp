
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;
using namespace lambda::$;

TEST(lambda, dollar) {
    ASSERT_EQ(12345, id(12345));

    ASSERT_EQ(array(1, 2, 3, 4), array(1, 2, 3, 4));

    ASSERT_EQ(vector(2, 3, 4, 5), map(vector(1, 2, 3, 4), plus(1)));

    ASSERT_EQ(vector(1, 4), without(vector(1, 2, 3, 4), 2, 3));
}
