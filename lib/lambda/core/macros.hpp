
#pragma once

#define let const auto

#define REQUIRE_CONCEPT(...) std::enable_if_t<(__VA_ARGS__), int> = 0
