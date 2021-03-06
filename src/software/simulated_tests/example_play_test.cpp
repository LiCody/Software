#include "software/ai/hl/stp/play/example_play.h"

#include <gtest/gtest.h>

#include "software/simulated_tests/simulated_test_fixture.h"
#include "software/simulated_tests/validation/validation_function.h"
#include "software/time/duration.h"
#include "software/world/world.h"

class ExamplePlayTest : public SimulatedTestFixture
{
};

TEST_F(ExamplePlayTest, test_example_play)
{
    setBallState(BallState(Point(-0.8, 0), Vector(0, 0)));
    addFriendlyRobots({
        RobotStateWithId{
            .id          = 0,
            .robot_state = RobotState(Point(4, 0), Vector(0, 0), Angle::zero(),
                                      AngularVelocity::zero())},
        RobotStateWithId{
            .id          = 1,
            .robot_state = RobotState(Point(0.5, 0), Vector(0, 0), Angle::zero(),
                                      AngularVelocity::zero())},
        RobotStateWithId{
            .id          = 2,
            .robot_state = RobotState(Point(-3, 1), Vector(0, 0), Angle::zero(),
                                      AngularVelocity::zero())},
        RobotStateWithId{
            .id          = 3,
            .robot_state = RobotState(Point(-1, -3), Vector(0, 0), Angle::zero(),
                                      AngularVelocity::zero())},
        RobotStateWithId{
            .id          = 4,
            .robot_state = RobotState(Point(2, 0), Vector(0, 0), Angle::zero(),
                                      AngularVelocity::zero())},
        RobotStateWithId{
            .id          = 5,
            .robot_state = RobotState(Point(3.5, 3), Vector(0, 0), Angle::zero(),
                                      AngularVelocity::zero())},
    });
    // Set the goalie ID to that of a non-existent robot so that all robots
    // take on non-goalie roles
    setFriendlyGoalie(99);
    setPlay(ExamplePlay::name);

    std::vector<ValidationFunction> terminating_validation_functions = {
        [](std::shared_ptr<World> world_ptr, ValidationCoroutine::push_type& yield) {
            auto friendly_robots_1_meter_from_ball =
                [](std::shared_ptr<World> world_ptr) {
                    Point ball_position = world_ptr->ball().position();
                    for (const auto& robot : world_ptr->friendlyTeam().getAllRobots())
                    {
                        double abs_error =
                            std::fabs((robot.position() - ball_position).length() - 1.0);
                        if (abs_error > 0.05)
                        {
                            return false;
                        }
                    }
                    return true;
                };

            while (!friendly_robots_1_meter_from_ball(world_ptr))
            {
                yield();
            }
        }};

    std::vector<ValidationFunction> non_terminating_validation_functions = {};

    runTest(terminating_validation_functions, non_terminating_validation_functions,
            Duration::fromSeconds(8));
}
