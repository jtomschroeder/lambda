
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;
using namespace lambda::factory;
using namespace lambda::streams;

TEST(lambda, stream) {
    auto s = stream(vector(1, 2, 3, 4)) | map(plus(1)) | filter(less(4));
    while (auto val = s.next()) {
        printer << val << '\n';
    }
}

TEST(lambda, stream1) {
    printer << (stream(vector(1, 2, 3, 4)) | map(plus(1)) | filter(less(4)) | fold(0, plus));
}

TEST(lambda, fold) { ASSERT_EQ(31, stream(vector(1, 2, 3, 4, 6, 7, 8)) | fold(0, plus)); }

TEST(lambda, sum) { ASSERT_EQ(31, stream(vector(1, 2, 3, 4, 6, 7, 8)) | sum); }
