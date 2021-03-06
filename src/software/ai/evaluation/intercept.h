#pragma once

#include <optional>

#include "software/new_geom/point.h"
#include "software/world/ball.h"
#include "software/world/field.h"
#include "software/world/robot.h"

/**
 * Finds the best place for the given robot to intercept the given ball
 *
 * @param ball The ball to intercept
 * @param field The field on which we want the intercept to occur
 * @param robot The robot that will hopefully intercept the ball
 *
 * @return A pair holding the best place that the robot can move to in order to
 * intercept the ball, and the duration into the future at which the pass would occur,
 *         relative to the timestamp of the robot. If no possible intercept could be
 * found within the field bounds, returns std::nullopt
 */
std::optional<std::pair<Point, Duration>> findBestInterceptForBall(Ball ball, Field field,
                                                                   Robot robot);
