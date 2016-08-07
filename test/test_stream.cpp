
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;
using namespace lambda::streams;

TEST(lambda, stream) {
    auto s = stream($::vector(1, 2, 3, 4)) | map(plus(1)) | filter(less(4));
    while (auto val = s.next()) {
        printer << val << '\n';
    }
}
