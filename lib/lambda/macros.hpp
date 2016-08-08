
#ifndef LAMBDA_MACROS_H
#define LAMBDA_MACROS_H

#define let const auto

#define REQUIRE_CONCEPT(...) std::enable_if_t<(__VA_ARGS__), int> = 0

#endif // LAMBDA_MACROS_H
