package(default_visibility = ["//software/ai:__subpackages__"])

cc_library(
    name = "path_manager",
    hdrs = [
        "path_manager.h",
        "path_objective.h",
    ],
    deps = [
        "//software/ai/navigator/obstacle",
        "//software/ai/navigator/path_planner",
        "//software/geom",
        "//software/world",
    ],
)

cc_library(
    name = "velocity_obstacle_path_manager",
    srcs = ["velocity_obstacle_path_manager.cpp"],
    hdrs = ["velocity_obstacle_path_manager.h"],
    deps = [
        ":path_manager",
        "//software/ai/navigator/obstacle:robot_navigation_obstacle_factory",
        "//software/parameter:dynamic_parameters",
    ],
)

cc_test(
    name = "velocity_obstacle_path_manager_test",
    srcs = ["velocity_obstacle_path_manager_test.cpp"],
    deps = [
        ":velocity_obstacle_path_manager",
        "//software/ai/navigator/path_planner:straight_line_path_planner",
        "//software/test_util",
        "@gtest//:gtest_main",
    ],
)
