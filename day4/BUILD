load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "lib",
    srcs = ["lib.cpp"],
    hdrs = ["lib.hpp"],
)
cc_binary(
    name = "part1",
    srcs = ["p1.cpp"],
    deps = [":lib"]
)

cc_binary(
    name = "part2",
    srcs = ["p2.cpp"],
    deps = [":lib"],
)