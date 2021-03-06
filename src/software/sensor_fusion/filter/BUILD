package(default_visibility = ["//software/sensor_fusion:__subpackages__"])

cc_library(
    name = "vision_detection",
    hdrs = [
        "vision_detection.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//software/new_geom:angle",
        "//software/new_geom:point",
        "//software/time:timestamp",
    ],
)

cc_library(
    name = "ball_filter",
    srcs = ["ball_filter.cpp"],
    hdrs = ["ball_filter.h"],
    deps = [
        ":vision_detection",
        "//software/geom",
        "//software/math:math_functions",
        "//software/new_geom/util:algorithms",
        "//software/world:ball",
        "//software/world:field",
        "@eigen",
    ],
)

cc_test(
    name = "ball_filter_test",
    srcs = ["ball_filter_test.cpp"],
    deps = [
        ":ball_filter",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "robot_filter",
    srcs = ["robot_filter.cpp"],
    hdrs = ["robot_filter.h"],
    deps = [
        ":vision_detection",
        "//software/geom",
        "//software/world:robot",
    ],
)

cc_test(
    name = "robot_filter_test",
    srcs = ["robot_filter_test.cpp"],
    deps = [
        ":robot_filter",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "robot_team_filter",
    srcs = ["robot_team_filter.cpp"],
    hdrs = ["robot_team_filter.h"],
    deps = [
        ":robot_filter",
        "//software:constants",
        "//software/world:team",
    ],
)

cc_test(
    name = "robot_team_filter_test",
    srcs = ["robot_team_filter_test.cpp"],
    deps = [
        ":robot_team_filter",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "sensor_fusion_filters",
    deps = [
        ":ball_filter",
        ":robot_team_filter",
    ],
)
