
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;

auto id(int n) { return some(n); }
auto id_s(int n) { return some(std::to_string(n)); }

class Dollar {
public:
    Dollar() {}

    template <class R, class F>
    auto map(R r, F &&f) const {
        std::transform(r.begin(), r.end(), r.begin(), [&](auto i) { return f(i); });
        return r;
    }

    template <class... Types>
    constexpr std::vector<std::common_type_t<Types...>> vector(Types &&... args) const {
        return {args...};
    }
} static const $;

TEST(lambda, maybe) {
    let num = some(1024);
    ASSERT_TRUE(bool(num));

    let n = num >> id >> id_s >> ([](auto s) { return some(s + "!"); });
    ASSERT_EQ("1024!", *n);

    $.map($.vector(1, 2, 3, 4), plus(1));
}
